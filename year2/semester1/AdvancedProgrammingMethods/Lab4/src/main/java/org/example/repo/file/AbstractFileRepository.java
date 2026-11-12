package org.example.repo.file;

import org.example.domain.Entity;
import org.example.repo.RepositoryException;
import org.example.repo.RepositoryInMemory;
import org.example.validator.ValidationException;
import org.example.validator.Validator;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.format.DateTimeParseException;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends RepositoryInMemory<ID, E> {
    private final String fileName;
    private final Validator<E> validator;

    public AbstractFileRepository(String fileName, Validator<E> validator) {
        super();
        this.fileName = fileName;
        this.validator = validator;
        loadFromFile();
    }

    protected abstract E extractEntity(String line);

    protected abstract String createEntityAsString(E entity);

    private void loadFromFile() {
        Path path = Paths.get(fileName);

        if (!Files.exists(path)) {
            return;
        }

        try (Stream<String> lines = Files.lines(path)) {
            lines.filter(line -> !line.trim().isEmpty()).map(line -> {
                try {
                    E entity = extractEntity(line);
                    validator.validate(entity);
                    return entity;
                } catch (NumberFormatException | DateTimeParseException | IndexOutOfBoundsException |
                         ValidationException e) {
                    System.err.println("Corrupt or invalid line at " + fileName + ": " + line);
                    return null;
                }
            }).filter(Objects::nonNull).forEach(super::save);
        }

        catch(IOException e){
            throw new RepositoryException("Failed to read file: " + fileName, e);
        }
    }

    private void saveToFile() {
        Path path = Paths.get(fileName);

        try {
            if (path.getParent() != null && !Files.exists(path.getParent())) {
                Files.createDirectories(path.getParent());
            }

            List<String> lines = StreamSupport.stream(super.findAll().spliterator(), false)
                    .map(this::createEntityAsString).toList();

            Files.write(path, lines);
        }

        catch (IOException e) {
            throw new RepositoryException("Failed to save file: " + fileName, e);
        }
    }

    @Override
    public Optional<E> save(E entity) {
        Optional<E> result = super.save(entity);
        if (result.isEmpty()) {
            saveToFile();
        }

        return result;
    }

    @Override
    public Optional<E> delete(ID id) {
        Optional<E> result = super.delete(id);
        if (result.isPresent()) {
            saveToFile();
        }

        return result;
    }

    @Override
    public Optional<E> update(E entity) {
        Optional<E> result = super.update(entity);
        if (result.isEmpty()) {
            saveToFile();
        }

        return result;
    }
}
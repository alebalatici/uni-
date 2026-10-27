package org.example.repo.file;

import org.example.domain.Entity;
import org.example.repo.RepositoryException;
import org.example.repo.RepositoryInMemory;
import org.example.validator.ValidationException;
import org.example.validator.Validator;

import java.io.*;
import java.time.format.DateTimeParseException;

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
        File file = new File(fileName);

        if (!file.exists()) {
            return;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            int lineNumber = 0;

            while ((line = reader.readLine()) != null) {
                lineNumber++;
                if (line.trim().isEmpty()) {
                    continue;
                }

                try {
                    E entity = extractEntity(line);
                    validator.validate(entity);
                    super.save(entity);
                }
                catch (NumberFormatException | DateTimeParseException | IndexOutOfBoundsException |
                       ValidationException e) {
                    //throw new RepositoryException("Corrupt or invalid line at " + fileName + " lineNumber " + lineNumber + ": " + line, e);
                    System.err.println("Corrupt or invalid line at " + fileName + " lineNumber " + lineNumber + ": " + line);
                }
            }
        }

        catch (IOException e) {
            throw new RepositoryException("Failed to read file: " + fileName, e);
        }
    }

    private void saveToFile() {
        File file = new File(fileName);

        if (file.getParentFile() != null && !file.getParentFile().exists()) {
            file.getParentFile().mkdirs();
            System.out.println("Hello world");
        }

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
            for (E entity : super.findAll()) {
                writer.write(createEntityAsString(entity));
                writer.newLine();
            }
        }
        catch (IOException e) {
            throw new RepositoryException("Failed to save file: " + fileName, e);
        }
    }

    @Override
    public E save(E entity) {
        E result = super.save(entity);
        if (result == null) {
            saveToFile();
        }

        return result;
    }

    @Override
    public E delete(ID id) {
        E result = super.delete(id);
        if (result != null) {
            saveToFile();
        }

        return result;
    }

    @Override
    public E update(E entity) {
        E result = super.update(entity);
        if (result == null) {
            saveToFile();
        }

        return result;
    }
}
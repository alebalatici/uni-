package org.example.repo;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import com.fasterxml.jackson.datatype.jsr310.JavaTimeModule;
import org.example.domain.Entity;

import java.io.File;
import java.io.IOException;
import java.util.List;

/**
 * Abstract repository implementation that persists entities in JSON format using Jackson
 * <p>
 *     Extends {@link RepositoryInMemory} to keep entities in memory while synchronizing
 *     changes (save, delete, update) with a physical JSON file on disk
 * </p>
 * @param <ID> the type of the entity's unique identifier
 * @param <E> the entity type, extending {@link Entity}
 */
public abstract class AbstractJsonRepository <ID, E extends Entity<ID>> extends RepositoryInMemory<ID, E> {
    private final String fileName;
    protected final ObjectMapper objectMapper;

    /**
     * Constructs an {@code AbstractJsonRepository} with the specified JSON file path
     * Configures the Jackson {@link ObjectMapper} for Date/Time support and printing then loads initial data from the file
     * @param fileName the path to the JSON file used for persistence
     */
    public AbstractJsonRepository(String fileName) {
        super();
        this.fileName = fileName;
        this.objectMapper = new ObjectMapper();
        this.objectMapper.registerModule(new JavaTimeModule());
        this.objectMapper.disable(SerializationFeature.WRITE_DATES_AS_TIMESTAMPS);
        this.objectMapper.enable(SerializationFeature.INDENT_OUTPUT);

        loadData();
    }

    /**
     * Loads initial data from the JSON file into the in-memory repository
     * @throws RepositoryException if an I/O error occurs while reading the file
     */
    private void loadData() {
        File file = new File(fileName);
        if (!file.exists()) {
            return;
        }

        try {
            List<E> list = readFromFile(file);
            for (E entity : list) {
                super.save(entity);
            }
        }
        catch (IOException e) {
            throw new RepositoryException(e.getMessage());
        }
    }

    /**
     * Writes all currently stored in-memory entities back to the JSON file
     * @throws RepositoryException if an I/O error occurs while writing to the file
     */
    private void saveData() {
        try {
            objectMapper.writeValue(new File(fileName), findAll());
        }

        catch (IOException e) {
            throw new RepositoryException(e.getMessage());
        }
    }

    /**
     * Reads a list of entities from the specified JSON file
     * Must be implemented by concrete subclasses to handle specific type deserialization
     * @param file the JSON file to read from
     * @return a list of deserialized entities
     * @throws IOException if an I/O or JSON parsing error occurs
     */
    protected abstract List<E> readFromFile(File file) throws IOException;

    /**
     * Saves an entity in memory and synchronizes the change to the JSON file if successful
     * @param entity the entity to be saved
     * @return {@code null} if the entity was saved, or the existing entity if the ID already exists
     */
    @Override
    public E save(E entity) {
        E result = super.save(entity);
        if (result == null) {
            saveData();
        }

        return result;
    }

    /**
     * Deletes an entity from memory and updates the JSON file if an entity was removed
     * @param id the ID of the entity to delete
     * @return the removed entity, or {@code null} if no entity existed with the given ID
     */
    @Override
    public E delete(ID id) {
        E result = super.delete(id);
        if (result != null) {
            saveData();
        }

        return result;
    }

    /**
     * Updates an entity in memory and synchronizes the change to the JSON file if successful
     * @param entity the entity containing updated fields
     * @return {@code null} if updated successfully, or the entity if it was not found
     */
    @Override
    public E update(E entity) {
        E result = super.update(entity);
        if (result == null) {
            saveData();
        }

        return result;
    }
}
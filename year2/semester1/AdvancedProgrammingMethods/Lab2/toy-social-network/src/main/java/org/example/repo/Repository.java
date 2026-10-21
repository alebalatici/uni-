package org.example.repo;

import org.example.domain.Entity;

/**
 * CRUD repository interface for managing entities of type {@code E} with a unique identifier of type {@code ID}
 * @param <ID> the type of the entity's unique identifier
 * @param <E> the entity type, which must extend {@link Entity}
 */
public interface Repository<ID, E extends Entity<ID>> {
    /**
     * Saves a new entity
     * @param entity The entity to be saved
     * @return {@code null} if the entity is saved successfully
     */
    E save(E entity);

    /**
     * Finds an entity after an ID
     * @param id the ID of the entity to be found
     * @return the entity with the given ID or {@code null} if it does not exist
     */
    E find(ID id);

    /**
     * Returns all the entities stored
     * @return an {@link Iterable} containing all stored entities
     */
    Iterable<E> findAll();

    /**
     * Deletes an entity with a given ID
     * @param id the ID of the entity to be deleted
     * @return the deleted entity, or {@code null} if no entity with the given ID exists
     */
    E delete(ID id);

    /**
     * Updates an existing entity
     * @param entity the entity with the new data
     * @return {@code null} if the update was done successfully
     */
    E update(E entity);
}
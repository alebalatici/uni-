package org.example.repo;

import org.example.domain.Entity;

/**
 * CRUD repository interface for managing entities of type {@code E} with a unique identifier of type {@code ID}
 * @param <ID> the type of the entity's unique identifier
 * @param <E> the entity type, which must extend {@link Entity}
 */
public interface Repository<ID, E extends Entity<ID>> {
    /**
     * Saves a new entity in the repository
     * @param entity the entity to save; must not be null
     * @return {@code null} if the entity was saved successfully, or the entity itself if it already exists
     * @throws IllegalArgumentException if the given entity is null
     * @throws RepositoryException     if an entity with the same ID already exists
     */
    E save(E entity);

    /**
     * Finds an entity by its unique ID
     * @param id the ID of the entity to search for; must not be null
     * @return the entity with the given ID, or {@code null} if no such entity exists
     * @throws IllegalArgumentException if the given ID is null
     */
    E find(ID id);

    /**
     * Returns all the entities stored
     * @return an {@link Iterable} containing all stored entities
     */
    Iterable<E> findAll();

    /**
     * Removes an entity by its unique ID
     * @param id the ID of the entity to delete; must not be null
     * @return the removed entity, or {@code null} if no entity was found with the given ID
     * @throws IllegalArgumentException if the given ID is null
     * @throws RepositoryException     if the entity to delete does not exist
     */
    E delete(ID id);

    /**
     * Updates an existing entity
     * @param entity the entity with updated information; must not be null
     * @return {@code null} if the entity was successfully updated, or the entity itself if it does not exist
     * @throws IllegalArgumentException if the given entity is null
     * @throws RepositoryException     if the entity to update does not exist
     */
    E update(E entity);
}
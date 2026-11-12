package org.example.repo;

import org.example.domain.Entity;

import java.util.List;
import java.util.Optional;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

/**
 * CRUD repository interface for managing entities of type {@code E} with a unique identifier of type {@code ID}
 * @param <ID> the type of the entity's unique identifier
 * @param <E> the entity type, which must extend {@link Entity}
 */
public interface Repository<ID, E extends Entity<ID>> {
    /**
     * Saves a new entity in the repository
     * @param entity the entity to save; must not be null
     * @return {@link Optional} if the entity was saved successfully, or the entity itself if it already exists
     * @throws IllegalArgumentException if the given entity is null
     * @throws RepositoryException     if an entity with the same ID already exists
     */
    Optional<E> save(E entity);

    /**
     * Finds an entity by its unique ID
     * @param id the ID of the entity to search for; must not be null
     * @return the entity with the given ID, or {@link Optional} if no such entity exists
     * @throws IllegalArgumentException if the given ID is null
     */
    Optional<E> findOne(ID id);

    /**
     * Returns all the entities stored
     * @return an {@link Iterable} containing all stored entities
     */
    Iterable<E> findAll();

    /**
     * Removes an entity by its unique ID
     * @param id the ID of the entity to delete; must not be null
     * @return the removed entity, or {@link Optional} if no entity was found with the given ID
     * @throws IllegalArgumentException if the given ID is null
     * @throws RepositoryException     if the entity to delete does not exist
     */
    Optional<E> delete(ID id);

    /**
     * Updates an existing entity
     * @param entity the entity with updated information; must not be null
     * @return {@link Optional} if the entity was successfully updated, or the entity itself if it does not exist
     * @throws IllegalArgumentException if the given entity is null
     * @throws RepositoryException     if the entity to update does not exist
     */
    Optional<E> update(E entity);

    /**
     * Returns a list of all entries in the repository that satisfy the given predicate filter
     * <p>
     *     This default implementation retrieves all entities via {@link #findAll()}, converts the resulting {@link Iterable} into a sequential stream, and filters the elements based on the provided predicate
     * </p>
     * @param filter the {@link Predicate} used to evaluate each entity: must not be null
     * @return a {@link List} containing all entities that match the specified filter criteria, or an empty list if no entities match
     * @throws NullPointerException if the specified filter is {@code null}
     */
    default List<E> findAll(Predicate<E> filter) {
        return StreamSupport.stream(findAll().spliterator(), false).filter(filter).collect(Collectors.toList());
    }
}
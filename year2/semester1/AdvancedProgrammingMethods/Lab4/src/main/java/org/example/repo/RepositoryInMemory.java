package org.example.repo;

import org.example.domain.Entity;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

/**
 * CRUD in-memory repository functions
 * @param <ID> the type of the entity's unique identifier
 * @param <E> the entity type, which must extend {@link Entity}
 */
public class RepositoryInMemory<ID, E extends Entity<ID>> implements Repository<ID, E> {
    /**
     * Map storing entities in memory indexed by their unique IDs
     */
    protected Map<ID, E> entities;

    /**
     * Constructs an empty {@code RepositoryInMemory} instance
     */
    public RepositoryInMemory() {
        this.entities = new HashMap<>();
    }

    @Override
    public Optional<E> save(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity is null");
        }

        if (entities.containsKey(entity.getId())) {
            throw new RepositoryException(entity.getId() + " already exists");
        }

        entities.put(entity.getId(), entity);
        return Optional.empty();
    }

    @Override
    public Optional<E> findOne(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("id is null");
        }
        return Optional.ofNullable(entities.get(id));
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }


    @Override
    public Optional<E> delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("id is null");
        }

        E removed = entities.remove(id);

        if (removed == null) {
            throw new RepositoryException(id + " was not deleted because it doesn't exist");
        }

        return Optional.of(removed);
    }

    @Override
    public Optional<E> update(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity is null");
        }

        if (!entities.containsKey(entity.getId())) {
            throw new RepositoryException(entity.getId() + " was not updated because it doesn't exist");
        }

        entities.put(entity.getId(), entity);
        return Optional.empty();
    }
}
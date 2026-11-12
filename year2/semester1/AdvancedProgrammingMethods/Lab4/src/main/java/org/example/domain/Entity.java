package org.example.domain;
import java.io.Serial;
import java.io.Serializable;
import java.util.Objects;

/**
 * Base abstract class for all domain entities in the system
 * An entity is uniquely identified by its ID
 * @param <ID> the type of the unique identifier
 */
public abstract class Entity<ID> implements Serializable {
    @Serial
    private static final long serialVersionUID = 1L;

    private ID id;

    /**
     * Gets the unique identifier of the entity
     * @return the entity ID
     */
    public ID getId() {
        return id;
    }

    /**
     * Sets the unique identifier of the entity
     * @param id the new entity ID
     */
    public void setId(ID id) {
        this.id = id;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Entity<?> entity = (Entity<?>) o;
        return Objects.equals(id, entity.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    @Override
    public String toString() {
        return "Entity{" + id + "}";
    }
}

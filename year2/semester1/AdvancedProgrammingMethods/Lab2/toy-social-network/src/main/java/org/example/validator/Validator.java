package org.example.validator;

/**
 * Generic interface for validating domain entities
 * @param <E> the type of entity to be validated
 */
public interface Validator<E> {
    /**
     * Validates the specified entity against business rules
     * @param entity the entity to validate
     * @throws ValidationException ValidationException if the entity violates any validation rules
     */
    void validate(E entity) throws ValidationException;
}
package org.example.validator;

/**
 * Generic interface for validating domain entities
 * @param <E> the type of entity to be validated
 */
@FunctionalInterface
public interface Validator<E> {
    /**
     * Validates the specified entity against business rules
     * @param entity the entity to validate
     * @throws ValidationException ValidationException if the entity violates any validation rules
     */
    void validate(E entity) throws ValidationException;

    /**
     * Combines this validator with another validator sequentially
     * @param other the validator to execute after this one
     * @return a new combined Validator
     */
    default Validator<E> andThen(Validator<E> other) {
        return (entity) -> {
            this.validate(entity);
            other.validate(entity);
        };
    }
}
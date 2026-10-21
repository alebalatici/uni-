package org.example.validator;

/**
 * Custom runtime exception thrown when domain entity validation fails
 */
public class ValidationException extends RuntimeException {
    /**
     * Constructs a new {@code ValidationException} with the specified detail message
     * @param message the detail message describing the validation errors
     */
    public ValidationException(String message) {
        super(message);
    }

    /**
     * Constructs a new {@code ValidationException} with the specified detail message and cause
     * @param message the detail message describing the validation error
     * @param cause the underlying cause of the exception
     */
    public ValidationException(String message, Throwable cause) {
        super(message, cause);
    }
}
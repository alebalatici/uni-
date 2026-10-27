package org.example.repo;

/**
 * Custom runtime exception thrown when repository operation fails
 */
public class RepositoryException extends RuntimeException {
    /**
     * Constructs a new {@code RepositoryException} with the specified detail message
     * @param message the detail message describing the repository operation error
     */
    public RepositoryException(String message) {
        super(message);
    }

    public RepositoryException(String message, Throwable cause) {
        super(message, cause);
    }
}
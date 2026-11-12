package org.example.service;

/**
 * Custom runtime exception thrown when service operation fails
 */
public class ServiceException extends RuntimeException {
    /**
     * Constructs a new {@code ServiceException} with the specified detail message
     * @param message the detail message describing the service errors
     */
    public ServiceException(String message) {
        super(message);
    }
}
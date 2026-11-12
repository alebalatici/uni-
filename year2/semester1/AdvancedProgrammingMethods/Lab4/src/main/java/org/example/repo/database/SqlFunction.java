package org.example.repo.database;

import java.sql.SQLException;

/**
 * Functional interface representing a function that accepts one argument and produces a result
 * allowing a {@link SQLException} to be thrown
 * @param <T> the type of the input to the function
 * @param <R> the type of the result of the function
 */
@FunctionalInterface
public interface SqlFunction<T, R> {
    /**
     * Applies this function to the given argument
     * @param t the input argument
     * @return the function result
     * @throws SQLException if a database access error occurs
     */
    R apply(T t) throws SQLException;
}
package org.example.repo.factory;

/**
 * Defines the supported persistence strategies for repository instantiation
 */
public enum RepositoryType {
    /**
     * In-memory storage strategy. Data is lost upon application restart
     */
    MEMORY,
    /**
     * File-based storage strategy using plain text persistence
     */
    FILE,
    /**
     * Relational database storage strategy using JDBC
     */
    DATABASE
}
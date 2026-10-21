package org.example.repo;

import com.fasterxml.jackson.core.type.TypeReference;
import org.example.domain.User;

import java.io.File;
import java.io.IOException;
import java.util.List;

/**
 * Concrete JSON repository implementation for managing {@link User} entities
 * Handles user-specific JSON serialization and deserialization
 */
public class UserRepository extends AbstractJsonRepository<Long, User> {
    /**
     * Constructs a {@code UserRepository} connected to the specified JSON file
     * @param fileName the path to the JSON file storing user data
     */
    public UserRepository(String fileName) {
        super(fileName);
    }

    @Override
    protected List<User> readFromFile(File file) throws IOException {
        return objectMapper.readValue(file, new TypeReference<List<User>>() {
        });
    }
}
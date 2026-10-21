package org.example.repo;

import com.fasterxml.jackson.core.type.TypeReference;
import org.example.domain.Friendship;
import org.example.domain.Tuple;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Type;
import java.util.List;

/**
 * Concrete JSON repository implementation for managing {@link Friendship} entities
 * Handles user-specific JSON serialization and deserialization
 */
public class FriendshipRepository extends AbstractJsonRepository<Tuple<Long, Long>, Friendship> {
    /**
     * Constructs a {@code FriendshipRepository} connected to the specified JSON file
     * @param fileName the path to the JSON file storing friendship data
     */
    public FriendshipRepository(String fileName) {
        super(fileName);
    }

    @Override
    protected List<Friendship> readFromFile(File file) throws IOException {
        return objectMapper.readValue(file, new TypeReference<List<Friendship>>() {});
    }
}
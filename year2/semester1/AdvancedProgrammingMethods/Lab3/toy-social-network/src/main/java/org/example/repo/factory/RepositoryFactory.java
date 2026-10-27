package org.example.repo.factory;

import org.example.domain.Friendship;
import org.example.domain.Tuple;
import org.example.domain.User;
import org.example.repo.Repository;
import org.example.repo.RepositoryException;
import org.example.repo.RepositoryInMemory;
import org.example.repo.database.FriendshipDbRepository;
import org.example.repo.database.UserDbRepository;
import org.example.repo.file.FriendshipFileRepository;
import org.example.repo.file.UserFileRepository;
import org.example.validator.Validator;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

/**
 * Factory class responsible for creating repository instances dynamically based on runtime configuration properties
 * <p>
 * Supports memory, file-based, and relational database persistence strategies
 * </p>
 */
public class RepositoryFactory {
    private final Properties properties;

    /**
     * Constructs a {@code RepositoryFactory} that loads configuration settings from the default {@code config.properties} resource file.
     * @throws RepositoryException if the {@code config.properties} file cannot be found or loaded
     */
    public RepositoryFactory() {
        this.properties = new Properties();
        try (InputStream input = RepositoryFactory.class.getClassLoader().getResourceAsStream("config.properties")) {
            if (input == null) {
                throw new RepositoryException("Could not find config.properties file in resources");
            }

            properties.load(input);
        }

        catch (IOException e) {
            throw new RepositoryException("Failed to load config.properties configuration", e);
        }
    }

    /**
     * Constructs a {@code RepositoryFactory} with custom configuration properties
     * @param properties the properties object containing repository configuration keys
     */
    public RepositoryFactory(Properties properties) {
        this.properties = properties;
    }

    /**
     * Parses and returns the configured {@link RepositoryType} from the properties object
     * @return the configured {@link RepositoryType}
     * @throws RepositoryException if the property 'repository.type' is missing or specifies an invalid repository type
     */
    private RepositoryType getRepositoryType() {
        String repoType = properties.getProperty("repository.type");
        if (repoType == null || repoType.trim().isEmpty()) {
            throw new RepositoryException("Property 'repository.type' is missing in config.properties");
        }

        try {
            return RepositoryType.valueOf(repoType.trim().toUpperCase());
        } catch (IllegalArgumentException e) {
            throw new RepositoryException("Unknown repository type in config.properties: " + repoType, e);
        }
    }

    /**
     * Creates a repository for managing {@link User} entities based on the configured repository type
     * @param userValidator the validator used to enforce constraints on user entities
     * @return a {@link Repository} instance for user entities
     * @throws RepositoryException if mandatory configuration properties for the chosen persistence type are missing
     */
    public Repository<Long, User> createUserRepository(Validator<User> userValidator) {
        RepositoryType repositoryType = getRepositoryType();

        switch (repositoryType) {
            case MEMORY: return new RepositoryInMemory<>();
            case FILE:
                String pathUsers = properties.getProperty("data.users");
                if (pathUsers == null || pathUsers.trim().isEmpty()) {
                    throw new RepositoryException("Property 'data.users' is missing in config.properties");
                }

                return new UserFileRepository(pathUsers, userValidator);

            case DATABASE:
                String url = properties.getProperty("db.url");
                String username = properties.getProperty("db.username");
                String password = properties.getProperty("db.password");

                if (url == null || username == null || password == null) {
                    throw new RepositoryException("Database configuration properties (url/username/password) are missing in config.properties");
                }

                return new UserDbRepository(userValidator, url, username, password);

            default:
                throw new RepositoryException("Unknown repository type in config.properties: " + repositoryType);
        }
    }

    /**
     * Creates a repository for managing {@link Friendship} relationships based on the configured repository type
     * @param friendshipValidator the validator used to enforce constraints on friendship relationships
     * @return a {@link Repository} instance for friendship entities
     * @throws RepositoryException if mandatory configuration properties for the chosen persistence type are missing
     */
    public Repository<Tuple<Long, Long>, Friendship> createFriendshipRepository(Validator<Friendship> friendshipValidator) {
        RepositoryType repositoryType = getRepositoryType();

        switch (repositoryType) {
            case MEMORY: return new RepositoryInMemory<>();
            case FILE:
                String pathFriendships = properties.getProperty("data.friendships");
                if (pathFriendships == null || pathFriendships.trim().isEmpty()) {
                    throw new RepositoryException("Property 'data.friendships' is missing in config.properties");
                }
                return new FriendshipFileRepository(pathFriendships, friendshipValidator);

            case DATABASE:
                String url = properties.getProperty("db.url");
                String username = properties.getProperty("db.username");
                String password = properties.getProperty("db.password");
                if (url == null || username == null || password == null) {
                    throw new RepositoryException("Database configuration (url/username/password) are missing in config.properties");
                }
                return new FriendshipDbRepository(friendshipValidator, url, username, password);
            default:
                throw new RepositoryException("Unknown repository type in config.properties: " + repositoryType);
        }
    }
}
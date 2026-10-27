package org.example;

import org.example.domain.Friendship;
import org.example.domain.Tuple;
import org.example.domain.User;
import org.example.repo.Repository;
import org.example.repo.RepositoryException;
import org.example.repo.RepositoryInMemory;
import org.example.repo.database.FriendshipDbRepository;
import org.example.repo.database.UserDbRepository;
import org.example.repo.factory.RepositoryFactory;
import org.example.repo.file.FriendshipFileRepository;
import org.example.repo.file.UserFileRepository;
import org.example.validator.FriendshipValidator;
import org.example.validator.UserValidator;
import org.example.validator.Validator;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.io.TempDir;

import java.nio.file.Path;
import java.util.Properties;

public class TestsRepositoryFactory {
    @TempDir
    Path tempDir;

    private Validator<User> userValidator;
    private Validator<Friendship> friendshipValidator;

    @BeforeEach
    void setUp() {
        userValidator = new UserValidator();
        friendshipValidator = new FriendshipValidator();

        String tempFilePathUsers = tempDir.resolve("test_users.txt").toString();
        String tempFilePathFriendships = tempDir.resolve("test_friendships.txt").toString();
    }

    @Test
    void createMemoryRepository() {
        Properties properties = new Properties();
        properties.setProperty("repository.type", "MEMORY");

        RepositoryFactory repositoryFactory = new RepositoryFactory(properties);

        Repository<Long, User> userRepository = repositoryFactory.createUserRepository(userValidator);
        Repository<Tuple<Long, Long>, Friendship> friendshipRepository = repositoryFactory.createFriendshipRepository(friendshipValidator);

        assertInstanceOf(RepositoryInMemory.class, userRepository);
        assertInstanceOf(RepositoryInMemory.class, friendshipRepository);
    }

    @Test
    void createConfigProperties() {
        RepositoryFactory repositoryFactory = new RepositoryFactory();

        Repository<Long, User> userRepository = repositoryFactory.createUserRepository(userValidator);
        Repository<Tuple<Long, Long>, Friendship> friendshipRepository = repositoryFactory.createFriendshipRepository(friendshipValidator);

        assertInstanceOf(RepositoryInMemory.class, userRepository);
        assertInstanceOf(RepositoryInMemory.class, friendshipRepository);

        assertInstanceOf(UserFileRepository.class, userRepository);
        assertInstanceOf(FriendshipFileRepository.class, friendshipRepository);

        assertNotNull(userRepository);
        assertNotNull(friendshipRepository);
    }

    @Test
    void testCreateFileRepository() {
        String userFile = tempDir.resolve("users.txt").toString();
        String friendshipFile = tempDir.resolve("friendships.txt").toString();

        Properties properties = new Properties();
        properties.setProperty("repository.type", "FILE");
        properties.setProperty("data.users", userFile);
        properties.setProperty("data.friendships", friendshipFile);

        RepositoryFactory repositoryFactory = new RepositoryFactory(properties);

        Repository<Long, User> userRepository = repositoryFactory.createUserRepository(userValidator);
        Repository<Tuple<Long, Long>, Friendship> friendshipRepository = repositoryFactory.createFriendshipRepository(friendshipValidator);

        assertInstanceOf(UserFileRepository.class, userRepository);
        assertInstanceOf(FriendshipFileRepository.class, friendshipRepository);

        assertNotNull(userRepository);
        assertNotNull(friendshipRepository);
    }

    @Test
    void testCreateDatabaseRepository() {
        Properties properties = new Properties();
        properties.setProperty("repository.type", "DATABASE");
        properties.setProperty("db.url", "jdbc:postgresql://localhost:5432/test");
        properties.setProperty("db.username", "postgres");
        properties.setProperty("db.password", "password");

        RepositoryFactory repositoryFactory = new RepositoryFactory(properties);

        Repository<Long, User> userRepository = repositoryFactory.createUserRepository(userValidator);
        Repository<Tuple<Long, Long>, Friendship> friendshipRepository = repositoryFactory.createFriendshipRepository(friendshipValidator);

        assertInstanceOf(UserDbRepository.class, userRepository);
        assertInstanceOf(FriendshipDbRepository.class, friendshipRepository);
    }

    @Test
    void testExceptions() {
        Properties properties = new Properties();
        RepositoryFactory repositoryFactory1 = new RepositoryFactory(properties);

        assertThrows(RepositoryException.class, () -> repositoryFactory1.createUserRepository(userValidator));

        properties.setProperty("repository.type", "ABC");
        RepositoryFactory repositoryFactory2 = new RepositoryFactory(properties);
        assertThrows(RepositoryException.class, () -> repositoryFactory2.createUserRepository(userValidator));

        properties.setProperty("repository.type", "FILE");
        RepositoryFactory repositoryFactory3 = new RepositoryFactory(properties);
        assertThrows(RepositoryException.class, () -> repositoryFactory3.createUserRepository(userValidator));

        String userFile = tempDir.resolve("users.txt").toString();
        String friendshipFile = tempDir.resolve("friendships.txt").toString();
        properties.setProperty("data.users", userFile);

        RepositoryFactory repositoryFactory4 = new RepositoryFactory(properties);
        assertDoesNotThrow(() -> repositoryFactory4.createUserRepository(userValidator));
        assertThrows(RepositoryException.class, () -> repositoryFactory4.createFriendshipRepository(friendshipValidator));

        properties.setProperty("data.friendships", friendshipFile);
        RepositoryFactory repositoryFactory5 = new RepositoryFactory(properties);
        assertDoesNotThrow(() -> repositoryFactory5.createFriendshipRepository(friendshipValidator));
    }
}
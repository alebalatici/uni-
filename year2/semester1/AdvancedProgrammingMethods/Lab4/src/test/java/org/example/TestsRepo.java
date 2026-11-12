package org.example;

import org.example.domain.Friendship;
import org.example.domain.Tuple;
import org.example.domain.User;
import org.example.repo.*;
import org.example.repo.file.FriendshipFileRepository;
import org.example.repo.file.UserFileRepository;
import org.example.utils.FileUtils;
import org.example.validator.FriendshipValidator;
import org.example.validator.UserValidator;
import org.example.validator.Validator;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

import java.nio.file.Path;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Optional;
import java.util.stream.StreamSupport;

import static org.junit.jupiter.api.Assertions.*;

public class TestsRepo {
    @TempDir
    Path tempDirUsers;

    @TempDir
    Path tempDirFriendships;

    private Repository<Long, User> userRepository;
    private Repository<Long, User> userRepositoryFile;
    private Repository<Tuple<Long, Long>, Friendship> friendshipRepository;
    private Repository<Tuple<Long, Long>, Friendship> friendshipRepositoryFile;

    @BeforeEach
    void setUp() {
        Validator<User> userValidator = new UserValidator();
        Validator<Friendship> friendshipValidator = new FriendshipValidator();

        userRepository = new RepositoryInMemory<>();
        friendshipRepository = new RepositoryInMemory<>();

        String tempFilePathUsers = tempDirUsers.resolve("test_users.txt").toString();
        FileUtils.copyTargetTemplate(tempFilePathUsers, "/users.txt");

        String tempFilePathFriendships = tempDirFriendships.resolve("test_friendships.txt").toString();
        FileUtils.copyTargetTemplate(tempFilePathFriendships, "/friendships.txt");

        userRepositoryFile = new UserFileRepository(tempFilePathUsers, userValidator);
        friendshipRepositoryFile = new FriendshipFileRepository(tempFilePathFriendships, friendshipValidator);
    }

    @Test
    void testSaveAndFindMemory() {
        User user1 = new User("username1", "firstName1", "lastName1", "email1@email.com", LocalDate.now());
        user1.setId(1L);
        User user2 = new User("username2", "firstName2", "lastName2", "email2@email.com", LocalDate.now());
        user2.setId(2L);
        User user3 = new User("username3", "firstName3", "lastName3", "email3@email.com", LocalDate.now());
        user3.setId(3L);

        assertTrue(userRepository.save(user1).isEmpty());
        assertTrue(userRepository.save(user2).isEmpty());
        assertTrue(userRepository.save(user3).isEmpty());

        assertEquals(3, StreamSupport.stream(userRepository.findAll().spliterator(), false).count());
        Optional<User> foundUser1 = userRepository.findOne(1L);
        assertTrue(foundUser1.isPresent());
        assertEquals(user1, foundUser1.get());

        Optional<User> foundUser2 = userRepository.findOne(2L);
        assertTrue(foundUser2.isPresent());
        assertEquals(user2, foundUser2.get());

        Optional<User> foundUser3 = userRepository.findOne(3L);
        assertTrue(foundUser3.isPresent());
        assertEquals(user3, foundUser3.get());
        assertTrue(userRepository.findOne(4L).isEmpty());

        User user4 = new User("username4", "firstName4", "lastName4", "email4@email.com", LocalDate.now());
        user4.setId(1L);

        assertThrows(RepositoryException.class, () -> userRepository.save(user4));
        assertThrows(IllegalArgumentException.class, () -> userRepository.save(null));
        assertThrows(IllegalArgumentException.class, () -> userRepository.findOne(null));
    }

    @Test
    void testDeleteMemory() {
        User user1 = new User("username1", "firstName1", "lastName1", "email1@email.com", LocalDate.now());
        user1.setId(1L);
        User user2 = new User("username2", "firstName2", "lastName2", "email2@email.com", LocalDate.now());
        user2.setId(2L);
        User user3 = new User("username3", "firstName3", "lastName3", "email3@email.com", LocalDate.now());
        user3.setId(3L);
        assertTrue(userRepository.save(user1).isEmpty());
        assertTrue(userRepository.save(user2).isEmpty());
        assertTrue(userRepository.save(user3).isEmpty());

        assertEquals(3, StreamSupport.stream(userRepository.findAll().spliterator(), false).count());
        assertEquals(user1, userRepository.delete(user1.getId()).orElse(null));
        assertEquals(2, StreamSupport.stream(userRepository.findAll().spliterator(), false).count());
        assertEquals(user2, userRepository.delete(user2.getId()).orElse(null));
        assertEquals(1, StreamSupport.stream(userRepository.findAll().spliterator(), false).count());
        assertEquals(user3, userRepository.delete(user3.getId()).orElse(null));

        assertThrows(RepositoryException.class, ()-> userRepository.delete(user1.getId()));
        assertThrows(IllegalArgumentException.class, ()-> userRepository.delete(null));
    }

    @Test
    void testUpdateMemory() {
        User user1 = new User("username1", "firstName1", "lastName1", "email1@email.com", LocalDate.now().minusYears(18));
        user1.setId(1L);
        User user2 = new User("username2", "firstName2", "lastName2", "email2@email.com", LocalDate.now().minusYears(18));
        user2.setId(2L);
        User user3 = new User("username3", "firstName3", "lastName3", "email3@email.com", LocalDate.now().minusYears(18));
        user3.setId(3L);
        assertTrue(userRepository.save(user1).isEmpty());
        assertTrue(userRepository.save(user2).isEmpty());
        assertTrue(userRepository.save(user3).isEmpty());
        assertEquals(3, StreamSupport.stream(userRepository.findAll().spliterator(), false).count());

        assertEquals("username1", userRepository.findOne(1L).map(User::getUsername).orElse(null));
        assertEquals("firstName1", userRepository.findOne(1L).map(User::getFirstName).orElse(null));
        assertEquals("lastName1", userRepository.findOne(1L).map(User::getLastName).orElse(null));
        assertEquals("email1@email.com", userRepository.findOne(1L).map(User::getEmail).orElse(null));
        assertEquals(LocalDate.now().minusYears(18), userRepository.findOne(1L).map(User::getBirthDate).orElse(null));

        User user4 = new User("username4", "firstName4", "lastName4", "email4@email.com", LocalDate.now().minusYears(18));
        user4.setId(1L);
        assertEquals(user1, user4);
        assertTrue(userRepository.update(user4).isEmpty());

        assertEquals("username4", userRepository.findOne(1L).map(User::getUsername).orElse(null));
        assertEquals("firstName4", userRepository.findOne(1L).map(User::getFirstName).orElse(null));
        assertEquals("lastName4", userRepository.findOne(1L).map(User::getLastName).orElse(null));
        assertEquals("email4@email.com", userRepository.findOne(1L).map(User::getEmail).orElse(null));
        assertEquals(LocalDate.now().minusYears(18), userRepository.findOne(1L).map(User::getBirthDate).orElse(null));
        assertEquals(3, StreamSupport.stream(userRepository.findAll().spliterator(), false).count());

        User user5 = new User("username5", "firstName5", "lastName5", "email5@email.com", LocalDate.now());
        user5.setId(1L);
        assertThrows(RepositoryException.class, ()-> userRepository.save(user5));
        assertThrows(IllegalArgumentException.class, ()-> userRepository.update(null));
    }

    @Test
    void testSaveAndFindFile() {
        assertEquals(10, StreamSupport.stream(userRepositoryFile.findAll().spliterator(), false).count());
        User user11 = new User("username11", "firstName11", "lastName11", "email11@email.com", LocalDate.now());
        user11.setId(11L);
        assertTrue(userRepositoryFile.save(user11).isEmpty());
        assertEquals(11, StreamSupport.stream(userRepositoryFile.findAll().spliterator(), false).count());
        assertThrows(IllegalArgumentException.class, ()-> userRepositoryFile.save(null));
        assertThrows(RepositoryException.class, ()-> userRepositoryFile.save(user11));

        Optional<User> user1 = userRepositoryFile.findOne(1L);
        assertTrue(user1.isPresent());
        assertEquals(1L, user1.get().getId());
        assertEquals("alex_m", user1.get().getUsername());
        assertEquals("Alexandra", user1.get().getFirstName());
        assertEquals("Pop", user1.get().getLastName());
        assertEquals("alex.pop@email.com", user1.get().getEmail());
        assertEquals("2000-05-15", user1.get().getBirthDate().toString());
        assertThrows(IllegalArgumentException.class, ()-> userRepositoryFile.findOne(null));
        assertTrue(userRepositoryFile.findOne(12L).isEmpty());
    }

    @Test
    void testDeleteFile() {
        assertEquals(10, StreamSupport.stream(userRepositoryFile.findAll().spliterator(), false).count());
        Optional<User> user1 = userRepositoryFile.findOne(1L);
        assertEquals(user1, userRepositoryFile.delete(1L));
        assertEquals(9, StreamSupport.stream(userRepositoryFile.findAll().spliterator(), false).count());
        assertThrows(IllegalArgumentException.class, ()-> userRepositoryFile.delete(null));
        assertThrows(RepositoryException.class, ()-> userRepositoryFile.delete(12L));
    }

    @Test
    void testUpdateFile() {
        User user11 = new User("username11", "firstName11", "lastName11", "email11@email.com", LocalDate.now().minusYears(18));
        user11.setId(1L);

        assertTrue(userRepositoryFile.findOne(1L).isPresent());
        assertTrue(userRepositoryFile.update(user11).isEmpty());
        assertEquals(10, StreamSupport.stream(userRepositoryFile.findAll().spliterator(), false).count());

        assertEquals("username11", userRepositoryFile.findOne(1L).get().getUsername());
        assertEquals("firstName11", userRepositoryFile.findOne(1L).get().getFirstName());
        assertEquals("lastName11", userRepositoryFile.findOne(1L).get().getLastName());
        assertEquals("email11@email.com", userRepositoryFile.findOne(1L).get().getEmail());
        assertEquals(LocalDate.now().minusYears(18), userRepositoryFile.findOne(1L).get().getBirthDate());
    }

    @Test
    void testAddFindDeleteUpdateFriendshipInMemory() {
        assertTrue(friendshipRepository.save(new Friendship(1L, 2L, LocalDateTime.now())).isEmpty());
        assertTrue(friendshipRepository.save(new Friendship(1L, 3L, LocalDateTime.of(2026, 10, 12, 10, 30))).isEmpty());
        assertTrue(friendshipRepository.save(new Friendship(2L, 5L, LocalDateTime.now().minusDays(5))).isEmpty());
        assertTrue(friendshipRepository.save(new Friendship(3L, 6L, LocalDateTime.now().minusDays(6))).isEmpty());
        assertTrue(friendshipRepository.save(new Friendship(4L, 7L, LocalDateTime.now().minusDays(7))).isEmpty());
        assertTrue(friendshipRepository.save(new Friendship(5L, 8L, LocalDateTime.now().minusDays(8))).isEmpty());
        assertTrue(friendshipRepository.save(new Friendship(6L, 9L, LocalDateTime.now().minusDays(9))).isEmpty());
        assertTrue(friendshipRepository.save(new Friendship(7L, 10L, LocalDateTime.now().minusDays(10))).isEmpty());
        assertEquals(8, StreamSupport.stream(friendshipRepository.findAll().spliterator(), false).count());
        assertThrows(IllegalArgumentException.class, ()-> friendshipRepository.save(null));

        assertNotNull(friendshipRepository.findOne(new Tuple<>(1L, 2L)));
        assertTrue(friendshipRepository.findOne(new Tuple<>(1L, 10L)).isEmpty());

        assertEquals(new Friendship(1L, 2L), friendshipRepository.delete(new Tuple<>(1L, 2L)).orElse(null));
        assertTrue(friendshipRepository.save(new Friendship(1L, 2L, LocalDateTime.now().minusDays(5))).isEmpty());
        assertEquals(new Friendship(1L, 2L), friendshipRepository.delete(new Tuple<>(2L, 1L)).orElse(null));

        assertEquals(7, StreamSupport.stream(friendshipRepository.findAll().spliterator(), false).count());
        assertThrows(IllegalArgumentException.class, ()-> friendshipRepository.delete(null));
        assertThrows(RepositoryException.class, ()-> friendshipRepository.delete(new Tuple<>(1L, 10L)));

        assertEquals(LocalDateTime.of(2026, 10, 12, 10, 30), friendshipRepository.findOne(new Tuple<>(1L, 3L)).map(Friendship::getFriendsFrom).orElse(null));
        friendshipRepository.update(new Friendship(1L, 3L, LocalDateTime.of(2026, 10, 12, 11, 0)));
        assertEquals(LocalDateTime.of(2026, 10, 12, 11, 0), friendshipRepository.findOne(new Tuple<>(1L, 3L)).map(Friendship::getFriendsFrom).orElse(null));
        assertThrows(IllegalArgumentException.class, ()-> friendshipRepository.update(null));
        assertThrows(RepositoryException.class, ()-> friendshipRepository.update(new Friendship(1L, 2L, LocalDateTime.of(2026, 10, 12, 11, 0))));
    }

    @Test
    void testAddFindDeleteUpdateFriendshipInFile() {
        assertEquals(8, StreamSupport.stream(friendshipRepositoryFile.findAll().spliterator(), false).count());
        assertTrue(friendshipRepositoryFile.save(new Friendship(7L, 10L, LocalDateTime.now().minusDays(10))).isEmpty());
        assertEquals(9, StreamSupport.stream(friendshipRepositoryFile.findAll().spliterator(), false).count());
        assertThrows(IllegalArgumentException.class, ()-> friendshipRepositoryFile.save(null));

        assertNotNull(friendshipRepositoryFile.findOne(new Tuple<>(1L, 2L)));
        assertNotNull(friendshipRepositoryFile.findOne(new Tuple<>(2L, 1L)));

        assertTrue(friendshipRepositoryFile.findOne(new Tuple<>(1L, 10L)).isEmpty());

        assertEquals(new Friendship(1L, 2L), friendshipRepositoryFile.delete(new Tuple<>(1L, 2L)).orElse(null));
        assertTrue(friendshipRepositoryFile.save(new Friendship(1L, 2L, LocalDateTime.now().minusDays(5))).isEmpty());
        assertEquals(new Friendship(1L, 2L), friendshipRepositoryFile.delete(new Tuple<>(2L, 1L)).orElse(null));

        assertEquals(8, StreamSupport.stream(friendshipRepositoryFile.findAll().spliterator(), false).count());
        assertThrows(IllegalArgumentException.class, ()-> friendshipRepositoryFile.delete(null));
        assertThrows(RepositoryException.class, ()-> friendshipRepositoryFile.delete(new Tuple<>(1L, 10L)));

        assertEquals(LocalDateTime.of(2024, 2, 1, 14, 20), friendshipRepositoryFile.findOne(new Tuple<>(2L, 3L)).map(Friendship::getFriendsFrom).orElse(null));
        friendshipRepositoryFile.update(new Friendship(2L, 3L, LocalDateTime.of(2026, 10, 12, 11, 0)));
        assertEquals(LocalDateTime.of(2026, 10, 12, 11, 0), friendshipRepositoryFile.findOne(new Tuple<>(2L, 3L)).map(Friendship::getFriendsFrom).orElse(null));
        assertThrows(IllegalArgumentException.class, ()-> friendshipRepositoryFile.update(null));
        assertThrows(RepositoryException.class, ()-> friendshipRepositoryFile.update(new Friendship(1L, 2L, LocalDateTime.of(2026, 10, 12, 11, 0))));
    }
}
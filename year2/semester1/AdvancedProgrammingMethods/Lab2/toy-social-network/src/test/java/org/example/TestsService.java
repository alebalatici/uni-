package org.example;

import org.example.domain.Friendship;
import org.example.domain.Tuple;
import org.example.domain.User;
import org.example.repo.FriendshipRepository;
import org.example.repo.Repository;
import org.example.repo.RepositoryInMemory;
import org.example.repo.UserRepository;
import org.example.service.ServiceException;
import org.example.service.NetworkService;
import org.example.utils.FileUtils;
import org.example.validator.FriendshipValidator;
import org.example.validator.UserValidator;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

import static org.junit.jupiter.api.Assertions.*;

import java.lang.reflect.Method;
import java.nio.file.Path;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class TestsService {
    @TempDir
    Path tempDirUsers;

    @TempDir
    Path tempDirFriendships;

    private NetworkService networkService;
    private Repository<Long, User> userRepository;
    private Repository<Tuple<Long, Long>, Friendship> friendshipRepository;

    private Repository<Long, User> userRepositoryFile;
    private Repository<Tuple<Long, Long>, Friendship> friendshipRepositoryFile;
    private NetworkService networkServiceFile;

    @BeforeEach
    void setUp() {
        userRepository = new RepositoryInMemory<>();
        friendshipRepository = new RepositoryInMemory<>();
        networkService = new NetworkService(userRepository, friendshipRepository, new UserValidator(), new FriendshipValidator());

        String tempFilePathUsers = tempDirUsers.resolve("test_users.json").toString();
        FileUtils.copyTargetTemplate(tempFilePathUsers, "/users.json");

        String tempFilePathFriendships = tempDirFriendships.resolve("test_friendships.json").toString();
        FileUtils.copyTargetTemplate(tempFilePathFriendships, "/friendships.json");

        userRepositoryFile = new UserRepository(tempFilePathUsers);
        friendshipRepositoryFile = new FriendshipRepository(tempFilePathFriendships);
        networkServiceFile = new NetworkService(userRepositoryFile, friendshipRepositoryFile, new UserValidator(), new FriendshipValidator());
    }

    @Test
    void testAddUserAndFriendship() {
        networkService.addUser(1L, "username1", "firstName1", "lastName1", "email1@email.com", LocalDate.now().minusYears(18));
        networkService.addUser(2L, "username2", "firstName2", "lastName2", "email2@email.com", LocalDate.now().minusYears(18));
        networkService.addUser(3L, "username3", "firstName3", "lastName3", "email3@email.com", LocalDate.now().minusYears(18));

        assertEquals(3, networkService.getAllUsers().size());

        friendshipRepository.save(new Friendship(1L, 2L));
        friendshipRepository.save(new Friendship(2L, 3L));
        assertEquals(2, StreamSupport.stream(friendshipRepository.findAll().spliterator(), false).count());
        assertThrows(ServiceException.class, () -> networkService.addUser(1L, "username4", "firstName4", "lastName4", "email4@email.com", LocalDate.now().minusYears(18)));
    }

    @Test
    void testRemoveUserAndFriendship() {
        networkService.addUser(1L, "username1", "firstName1", "lastName1", "email1@email.com", LocalDate.now().minusYears(18));
        networkService.addUser(2L, "username2", "firstName2", "lastName2", "email2@email.com", LocalDate.now().minusYears(18));
        networkService.addUser(3L, "username3", "firstName3", "lastName3", "email3@email.com", LocalDate.now().minusYears(18));

        friendshipRepository.save(new Friendship(1L, 2L));
        friendshipRepository.save(new Friendship(2L, 3L));

        assertEquals(2, StreamSupport.stream(friendshipRepository.findAll().spliterator(), false).count());
        networkService.removeUser(1L);
        assertEquals(1, StreamSupport.stream(friendshipRepository.findAll().spliterator(), false).count());
        networkService.removeUser(2L);
        assertEquals(0, StreamSupport.stream(friendshipRepository.findAll().spliterator(), false).count());
        assertThrows(ServiceException.class, () -> networkService.removeUser(1L));
    }

    @Test
    void testUpdateUser() {
        networkService.addUser(1L, "username1", "firstName1", "lastName1", "email1@email.com", LocalDate.now().minusYears(18));
        networkService.addUser(2L, "username2", "firstName2", "lastName2", "email2@email.com", LocalDate.now().minusYears(18));
        networkService.addUser(3L, "username3", "firstName3", "lastName3", "email3@email.com", LocalDate.now().minusYears(18));
        networkService.updateUser(1L, "username4", "firstName4", "lastName4", "email4@email.com", LocalDate.now().minusYears(18));
        assertThrows(ServiceException.class, () -> networkService.updateUser(4L, "username5", "firstName5", "lastName5", "email5@email.com", LocalDate.now().minusYears(18)));
    }

    @Test
    void testFindUser() {
        assertNotNull(networkServiceFile.findUser(1L));
        User user = networkServiceFile.findUser(1L);
        assertEquals("alex_m", user.getUsername());
        assertEquals("Alexandra", user.getFirstName());
        assertEquals("Pop", user.getLastName());
        assertEquals("alex.pop@email.com", user.getEmail());
        assertEquals("2000-05-15", user.getBirthDate().toString());
        assertThrows(ServiceException.class, ()-> networkServiceFile.findUser(11L));
    }

    @Test
    void testFindFriendship() {
        assertNotNull(networkServiceFile.findFriendship(1L, 2L));
        Friendship friendship1 = networkServiceFile.findFriendship(1L, 2L);
        assertEquals("2024-01-15T10:30", friendship1.getFriendsFrom().toString());

        assertNotNull(networkServiceFile.findFriendship(2L, 1L));

        assertNotNull(networkServiceFile.findFriendship(2L, 3L));
        Friendship friendship2 = networkServiceFile.findFriendship(2L, 3L);
        assertEquals("2024-02-01T14:20", friendship2.getFriendsFrom().toString());

        assertNotNull(networkServiceFile.findFriendship(3L, 2L));

        assertThrows(ServiceException.class, ()-> networkServiceFile.findFriendship(1L, 3L));
    }

    @Test
    void testAddFriendship() {
        assertEquals(8, networkServiceFile.getAllFriendships().size());

        networkServiceFile.addFriendship(1L, 3L);
        assertEquals(9, networkServiceFile.getAllFriendships().size());

        networkServiceFile.addFriendship(1L, 8L, LocalDateTime.of(2024, 10, 10, 10, 0));
        assertEquals(10, networkServiceFile.getAllFriendships().size());
        assertEquals(LocalDateTime.of(2024, 10, 10, 10, 0), networkServiceFile.findFriendship(1L, 8L).getFriendsFrom());

        assertThrows(ServiceException.class, () -> networkServiceFile.addFriendship(null, 2L));
        assertThrows(ServiceException.class, () -> networkServiceFile.addFriendship(1L, null));
        assertThrows(ServiceException.class, () -> networkServiceFile.addFriendship(null, null));
        assertThrows(ServiceException.class, () -> networkServiceFile.addFriendship(1L, 11L));
        assertThrows(ServiceException.class, () -> networkServiceFile.addFriendship(11L, 1L));
    }

    @Test
    void testRemoveFriendship() {
        assertEquals(8, networkServiceFile.getAllFriendships().size());

        networkServiceFile.removeFriendship(1L, 2L);
        assertEquals(7, networkServiceFile.getAllFriendships().size());

        networkServiceFile.addFriendship(1L, 2L);
        assertEquals(8, networkServiceFile.getAllFriendships().size());
        networkServiceFile.removeFriendship(2L, 1L);

        assertThrows(ServiceException.class, ()-> networkServiceFile.removeFriendship(1L, 3L));
        assertThrows(ServiceException.class, ()-> networkServiceFile.removeFriendship(null, null));
        assertThrows(ServiceException.class, ()-> networkServiceFile.removeFriendship(1L, null));
        assertThrows(ServiceException.class, ()-> networkServiceFile.removeFriendship(null, 1L));
    }

    @Test
    void testBuildAdjacencyListAndNumberOfComunities() {
        Map<Long, List<Long>> adjacencyList = networkServiceFile.buildAdjacencyList();
        assertNotNull(adjacencyList);
        assertEquals(10, adjacencyList.size());
        assertEquals(2, adjacencyList.get(1L).size());
        assertEquals(2, adjacencyList.get(2L).size());
        assertEquals(1, adjacencyList.get(3L).size());
        assertEquals(1, adjacencyList.get(4L).size());
        assertEquals(1, adjacencyList.get(5L).size());
        assertEquals(2, adjacencyList.get(6L).size());
        assertEquals(2, adjacencyList.get(7L).size());
        assertEquals(2, adjacencyList.get(8L).size());
        assertEquals(2, adjacencyList.get(9L).size());

        assertEquals(2, networkServiceFile.getNumberOfComunities());
    }

    @Test
    void testLongestPathAndMostSociableComunity() {
        Map<Long, List<Long>> adjacencyList = networkServiceFile.buildAdjacencyList();
        assertNotNull(adjacencyList);
        List<Long> maxComponent = new ArrayList<>();
        Set<Long> visited = new HashSet<>();
        networkService.dfs(1L, adjacencyList, visited, maxComponent);
        assertEquals(7, networkService.getLongestPathInComponent(maxComponent, adjacencyList));
        assertEquals(maxComponent.stream().map(networkServiceFile::findUser).toList(), networkServiceFile.getMostSociableComunity());
    }
}
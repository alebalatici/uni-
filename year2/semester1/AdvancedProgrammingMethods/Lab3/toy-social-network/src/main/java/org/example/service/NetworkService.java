package org.example.service;

import org.example.domain.Friendship;
import org.example.domain.Tuple;
import org.example.domain.User;
import org.example.repo.Repository;
import org.example.repo.RepositoryException;
import org.example.validator.ValidationException;
import org.example.validator.Validator;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

/**
 * Service class managing the social network operations
 * <p>
 *     Provides business logic for managing users, friendships, and graph analytics
 *     such as finding connected components (communities) and the most sociable community
 * </p>
 */
public class NetworkService {
    private final Repository<Long, User> userRepository;
    private final Repository<Tuple<Long, Long>, Friendship> friendshipRepository;
    private final Validator<User> userValidator;
    private final Validator<Friendship> friendshipValidator;

    /**
     * Constructs a {@code NetworkService} with the required repositories and validators
     * @param userRepository repository for managing user entities
     * @param friendshipRepository repository for managing friendship relationships
     * @param userValidator validator for user entity constraints
     * @param friendshipValidator validator for friendship entity constraints
     */
    public NetworkService(Repository<Long, User> userRepository, Repository<Tuple<Long, Long>, Friendship> friendshipRepository, Validator<User> userValidator, Validator<Friendship> friendshipValidator) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
        this.userValidator = userValidator;
        this.friendshipValidator = friendshipValidator;
    }

    /**
     * Creates, validates, and saves a new user in the system
     * @param id        the unique identifier of the user
     * @param username  the unique username
     * @param firstName the user's first name
     * @param lastName  the user's last name
     * @param email     the user's email address
     * @param birthDate the user's birthdate
     * @throws ValidationException if the user attributes are invalid
     * @throws RepositoryException if a user with the given ID already exists
     */
    public void addUser(Long id, String username, String firstName, String lastName, String email, LocalDate birthDate) {
        User user = new User(username, firstName, lastName, email, birthDate);
        user.setId(id);

        userValidator.validate(user);
        userRepository.save(user);
    }

    /**
     * Removes a user by ID and automatically cascade-deletes all associated friendships
     * @param id the ID of the user to be removed
     * @throws ServiceException    if the user does not exist
     * @throws RepositoryException if a persistence error occurs during deletion
     */
    public void removeUser(Long id) {
        User user = userRepository.find(id);
        if (user == null) {
            throw new ServiceException(id + " was not deleted because it doesn't exist");
        }

        List<Tuple<Long, Long>> friendshipsToRemove = new ArrayList<>();
        for (Friendship f: friendshipRepository.findAll()) {
            if (f.getIdUser1().equals(id) || f.getIdUser2().equals(id)) {
                friendshipsToRemove.add(f.getId());
            }
        }

        for (Tuple<Long, Long> friendshipToRemove : friendshipsToRemove) {
            friendshipRepository.delete(friendshipToRemove);
        }
        userRepository.delete(id);
    }

    /**
     * Updates the information of an existing user
     * @param id        the ID of the user to update
     * @param username  the new username
     * @param firstName the new first name
     * @param lastName  the new last name
     * @param email     the new email address
     * @param birthDate the new birthdate
     * @throws ValidationException if user attributes are invalid
     * @throws RepositoryException if the user does not exist in the repository
     */
    public void updateUser(Long id, String username, String firstName, String lastName, String email, LocalDate birthDate) {
        User user = new User(username, firstName, lastName, email, birthDate);
        user.setId(id);
        userValidator.validate(user);
        userRepository.update(user);
    }

    /**
     * Retrieves all registered users in the network
     * @return a list of all users
     */
    public List<User> getAllUsers() {
        List<User> users = new ArrayList<>();
        for (User user: userRepository.findAll()) {
            users.add(user);
        }

        return users;
    }

    /**
     * Retrieves all existing friendships in the network
     * @return a list of all friendships
     */
    public List<Friendship> getAllFriendships() {
        List<Friendship> friendships = new ArrayList<>();
        for (Friendship friendship: friendshipRepository.findAll()) {
            friendships.add(friendship);
        }

        return friendships;
    }

    /**
     * Creates and saves a friendship with a specified creation date and time
     * @param user1Id     the ID of the first user
     * @param user2Id     the ID of the second user
     * @param friendsFrom the timestamp when the friendship started
     * @throws ServiceException    if either user does not exist in the system
     * @throws ValidationException if the friendship attributes are invalid
     * @throws RepositoryException if the friendship already exists
     */
    public void addFriendship(Long user1Id, Long user2Id, LocalDateTime friendsFrom) {
        Friendship friendship = new Friendship(user1Id, user2Id, friendsFrom);
        friendshipValidator.validate(friendship);

        if (userRepository.find(user1Id) == null ) {
            throw new ServiceException(user1Id + " doesn't exist in the system");
        }

        if (userRepository.find(user2Id) == null ) {
            throw new ServiceException(user2Id + " doesn't exist in the system");
        }

        friendshipRepository.save(friendship);
    }

    /**
     * Creates and saves a friendship starting at the current timestamp
     * @param user1Id the ID of the first user
     * @param user2Id the ID of the second user
     * @throws ServiceException    if either user does not exist in the system
     * @throws ValidationException if the friendship attributes are invalid
     * @throws RepositoryException if the friendship already exists
     */
    public void addFriendship(Long user1Id, Long user2Id) {
        addFriendship(user1Id, user2Id, LocalDateTime.now());
    }

    /**
     * Finds a user entity by its unique ID
     * @param id the ID of the user to search for
     * @return the found {@link User} entity
     * @throws ServiceException if no user exists with the given ID
     */
    public User findUser(Long id) {
        User user = userRepository.find(id);
        if (user == null) {
            throw new ServiceException("A user with the id " + id + " doesn't exist in the system");
        }
        return user;
    }

    /**
     * Finds a friendship relationship between two users
     * @param user1Id the ID of the first user
     * @param user2Id the ID of the second user
     * @return the found {@link Friendship} entity
     * @throws ServiceException if the friendship does not exist
     */
    public Friendship findFriendship(Long user1Id, Long user2Id) {
        Friendship friendship = friendshipRepository.find(new Tuple<>(user1Id, user2Id));
        if (friendship == null) {
            throw new ServiceException("A friendship between the users with the id's " + user1Id + " and " + user2Id + " doesn't exist in the system");
        }
        return friendship;
    }

    /**
     * Deletes a friendship relationship between two users
     * @param user1Id the ID of the first user
     * @param user2Id the ID of the second user
     * @throws IllegalArgumentException if either user ID is null
     * @throws RepositoryException if the friendship does not exist
     */
    public void removeFriendship(Long user1Id, Long user2Id) {
        if (user1Id == null || user2Id == null) {
            throw new IllegalArgumentException("One or both user id's are null");
        }

        friendshipRepository.delete(new Tuple<>(user1Id, user2Id));
    }

    /**
     * Builds an adjacency list representation of the social network graph
     * @return a map where each user ID maps to the list of IDs of their friends
     */
    public Map<Long, List<Long>> buildAdjacencyList() {
        Map<Long, List<Long>> adjacencyList = new HashMap<>();

        for (User user: userRepository.findAll()) {
            adjacencyList.put(user.getId(), new ArrayList<>());
        }

        for (Friendship friendship: friendshipRepository.findAll()) {
            Long user1Id = friendship.getIdUser1();
            Long user2Id = friendship.getIdUser2();

            if (adjacencyList.containsKey(user1Id) && adjacencyList.containsKey(user2Id)) {
                adjacencyList.get(user1Id).add(user2Id);
                adjacencyList.get(user2Id).add(user1Id);
            }
        }

        return adjacencyList;
    }

    /**
     * Calculates the total number of connected components (communities) in the network graph
     * @return the total number of communities
     */
    public int getNumberOfComunities() {
        Map<Long, List<Long>> adjacencyList = buildAdjacencyList();
        Set<Long> visited = new HashSet<>();
        int count = 0;

        for (Long userId: adjacencyList.keySet()) {
            if (!visited.contains(userId)) {
                count++;
                dfs(userId, adjacencyList, visited, null);
            }
        }

        return count;
    }

    /**
     * Performs a Depth-First Search (DFS) traversal to discover all nodes in a connected component
     * @param startNode the starting user ID for traversal
     * @param adjacencyList graph representation of user connections
     * @param visited set tracking visited user IDs
     * @param component optional list populated with discovered user IDs in the current component (can be {@code null})
     */
    public void dfs(Long startNode, Map<Long, List<Long>> adjacencyList, Set<Long> visited, List<Long> component) {
        visited.add(startNode);
        if (component != null) {
            component.add(startNode);
        }
        for (Long nodeId: adjacencyList.get(startNode)) {
            if (!visited.contains(nodeId)) {
                dfs(nodeId, adjacencyList, visited, component);
            }
        }
    }

    /**
     * Computes the maximum shortest path distance (graph diameter) within a given component using Breadth-First Search (BFS)
     * @param component list of user IDs in the component
     * @param adjacencyList graph representation of user connections
     * @return the longest path length found in the component
     */
    public int getLongestPathInComponent(List<Long> component, Map<Long, List<Long>> adjacencyList) {
        int maxDist = 0;

        for (Long startNode: component) {
            Map<Long, Integer> distances = new HashMap<>();
            Queue<Long> queue = new LinkedList<>();

            queue.add(startNode);
            distances.put(startNode, 0);

            while (!queue.isEmpty()) {
                Long currentNode = queue.poll();
                int dist = distances.get(currentNode);
                maxDist = Math.max(maxDist, dist);

                for (Long neighbour: adjacencyList.get(currentNode)) {
                    if (!distances.containsKey(neighbour)) {
                        distances.put(neighbour, dist + 1);
                        queue.add(neighbour);
                    }
                }
            }
        }
        return maxDist;
    }

    /**
     * Identifies the most sociable comunity in the network, defined as the connected component
     * with the longest simple path (maximum diameter)
     * @return a list of {@link User} entities belonging to the most sociable community
     */
    public List<User> getMostSociableComunity() {
        Map<Long, List<Long>> adjacencyList = buildAdjacencyList();
        Set<Long> visited = new HashSet<>();

        List<Long> mostSociableComunity = new ArrayList<>();
        int maxPathLength = -1;

        for (Long userId: adjacencyList.keySet()) {
            if (!visited.contains(userId)) {
                List<Long> currentComponent = new ArrayList<>();
                dfs(userId, adjacencyList, visited, currentComponent);

                int currentMaxPath = getLongestPathInComponent(currentComponent, adjacencyList);

                if (currentMaxPath > maxPathLength) {
                    maxPathLength = currentMaxPath;
                    mostSociableComunity = currentComponent;
                }
            }
        }

        List<User> result = new ArrayList<>();
        for (Long userId: mostSociableComunity) {
            result.add(findUser(userId));
        }

        return result;
    }
}
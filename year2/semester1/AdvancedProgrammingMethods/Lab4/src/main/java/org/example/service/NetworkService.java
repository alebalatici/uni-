package org.example.service;

import org.example.domain.Friendship;
import org.example.domain.Tuple;
import org.example.domain.User;
import org.example.repo.Repository;
import org.example.repo.RepositoryException;
import org.example.utils.UserCriteria;
import org.example.validator.ValidationException;
import org.example.validator.Validator;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;
import java.util.function.Predicate;
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
        User user = userRepository.findOne(id).orElseThrow(() -> new ServiceException(id + " was not deleted because it doesn't exist"));

        List<Tuple<Long, Long>> friendshipsToRemove = StreamSupport.stream(friendshipRepository.findAll().spliterator(), false)
                        .filter(friendship -> friendship.getIdUser1().equals(id) || friendship.getIdUser2().equals(id))
                        .map(Friendship::getId)
                        .toList();

        friendshipsToRemove.forEach(friendshipRepository::delete);
        userRepository.delete(id);
    }

    /**
     * Updates the information of an existing user
     * @param id the ID of the user to update
     * @param username the new username
     * @param firstName the new first name
     * @param lastName the new last name
     * @param email the new email address
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
        return StreamSupport.stream(userRepository.findAll().spliterator(), false).collect(Collectors.toList());
    }

    /**
     * Retrieves all existing friendships in the network
     * @return a list of all friendships
     */
    public List<Friendship> getAllFriendships() {
        return StreamSupport.stream(friendshipRepository.findAll().spliterator(), false).collect(Collectors.toList());
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
        userRepository.findOne(user1Id).orElseThrow(() -> new ServiceException(user1Id + " doesn't exist in the system"));
        userRepository.findOne(user2Id).orElseThrow(() -> new ServiceException(user2Id + " doesn't exist in the system"));

        Friendship friendship = new Friendship(user1Id, user2Id, friendsFrom);
        friendshipValidator.validate(friendship);

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
        return userRepository.findOne(id).orElseThrow(() -> new ServiceException(id + " was not found in the system"));
    }

    /**
     * Finds a friendship relationship between two users
     * @param user1Id the ID of the first user
     * @param user2Id the ID of the second user
     * @return the found {@link Friendship} entity
     * @throws ServiceException if the friendship does not exist
     */
    public Friendship findFriendship(Long user1Id, Long user2Id) {
        return friendshipRepository.findOne(new Tuple<>(user1Id, user2Id)).orElseThrow(() -> new ServiceException("A friendship between the users with the id's " + user1Id + " and " + user2Id + " doesn't exist in the system"));
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
     * Returns a list of {@link User} entities corresponding to the specified list of IDs
     * <p>
     * Missing users (IDs not found in the repository) are skipped automatically.
     * </p>
     * @param ids the list of user IDs to retrieve; must not be null
     * @return a list of found {@link User} entities
     */
    public List<User> getUsersFromIdList(List<Long> ids) {
        return ids.stream()
                .map(userRepository::findOne)
                .filter(Optional::isPresent)
                .map(Optional::get)
                .collect(Collectors.toList());
    }

    /**
     * Retrieves a list of users whose first and last names match the specified values
     * @param firstName the first name to search for (case-insensitive); must not be null
     * @param lastName  the last name to search for (case-insensitive); must not be null
     * @return a {@link List} of matching {@link User} entities, or an empty list if no matches are found
     */
    public List<User> findUsersByName(String firstName, String lastName) {
        Predicate<User> firstNameAndLastName = UserCriteria.hasFirstName(firstName).and(UserCriteria.hasLastName(lastName));
        return userRepository.findAll(firstNameAndLastName);
    }

    /**
     * Retrieves a list of users whose email address belongs to the specified domain
     * @param emailDomain the domain name to search for (e.g., "gmail.com"); must not be null
     * @return a {@link List} of matching {@link User} entities, or an empty list if no matches are found
     */
    public List<User> findUsersByEmailDomain(String emailDomain) {
        Predicate<User> hasEmail = UserCriteria.hasEmailDomain(emailDomain);
        return userRepository.findAll(hasEmail);
    }

    /**
     * Retrieves a list of users who meet or exceed the specified minimum age
     * @param minimumAge the minimum required age in years
     * @return a {@link List} of {@link User} entities satisfying the age constraint, or an empty list if no matches are found
     */
    public List<User> findUsersByMinimumAge(int minimumAge) {
        Predicate<User> hasMinimumAge = UserCriteria.hasMinimumAge(minimumAge);
        return userRepository.findAll(hasMinimumAge);
    }

    /**
     * Sorts a list of users after a full given name
     * @param users the list of users to be sorted
     * @return the sorted list
     */
    public static List<User> getSortedByNameUsers(List<User> users) {
        return users.stream().sorted(Comparator.comparing(User::getLastName).thenComparing(User::getFirstName)).collect(Collectors.toList());
    }

    /**
     * Sorts a list of users after their age
     * @param users the list of users to be sorted
     * @return the sorted list
     */
    public static List<User> getSortedByAgeDesc(List<User> users) {
        return users.stream().sorted(Comparator.comparing(User::getBirthDate).reversed()).collect(Collectors.toList());
    }

    /**
     * Retrieves all registered users in the network who currently have no friends.
     * <p>
     * Populates each user's internal friends list dynamically based on the current
     * network topology (using the friendship adjacency list) and applies the
     * {@link UserCriteria#hasNoFriends(User)} static predicate via Stream filtering.
     * </p>
     * @return a {@link List} of {@link User} entities with no active friendships,
     *         or an empty list if all users have at least one friend
     */
    public List<User> getUsersWithNoFriends() {
        List<User> users = getAllUsers();
        List<Friendship> friendships = getAllFriendships();

        Map<Long, List<Long>> adjacencyList = GraphService.buildAdjacencyList(users, friendships);

        users.forEach(user -> {
            List<Long> friendsIds = adjacencyList.getOrDefault(user.getId(), Collections.emptyList());
            user.getFriends().clear();
            user.getFriends().addAll(getUsersFromIdList(friendsIds));
        });

        return users.stream().filter(UserCriteria::hasNoFriends).collect(Collectors.toList());
    }
}
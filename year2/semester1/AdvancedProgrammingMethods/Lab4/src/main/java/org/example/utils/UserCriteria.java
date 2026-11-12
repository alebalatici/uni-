package org.example.utils;

import org.example.domain.User;

import java.time.LocalDate;
import java.util.function.Predicate;

/**
 * Utility class providing static {@link Predicate} factory methods for filtering {@link User} entities
 */
public final class UserCriteria {
    /**
     * Private constructor to prevent instantiation of this utility class
     */
    private UserCriteria() {

    }

    /**
     * Creates a predicata that checks if a user's last name matches the specified name (case-insensitive)
     * @param lastName the last name to match
     * @return a {@link Predicate} evaluating user's last name
     */
    public static Predicate<User> hasLastName(String lastName) {
        return user -> user != null && user.getLastName().equalsIgnoreCase(lastName);
    }

    /**
     * Creates a predicate that checks if a user's first name matches the specified name (case-insensitive)
     * @param firstName the first name to match
     * @return a {@link Predicate} evaluating user's first name
     */
    public static Predicate<User> hasFirstName(String firstName) {
        return user -> user != null && user.getFirstName().equalsIgnoreCase(firstName);
    }

    /**
     * Creates a predicate that checks if a user's email ends with the specified domain
     * @param emailDomain the email domain to match (e.g., "gmail.com")
     * @return a {@link Predicate} evaluating user's email domain
     */
    public static Predicate<User> hasEmailDomain(String emailDomain) {
        return user -> user != null && user.getEmail() != null && user.getEmail().endsWith("@" + emailDomain);
    }

    /**
     * Creates a predicate that checks if a user meets or exceeds a minimum age requirement
     * @param minAge the minimum age in years
     * @return a {@link Predicate} evaluating user's age
     */
    public static Predicate<User> hasMinimumAge(int minAge) {
        return user -> user != null && user.getBirthDate() != null && LocalDate.now().minusYears(minAge).isAfter(user.getBirthDate());
    }

    /**
     * Evaluates whether a user has no registered friends
     * <p>
     * Checks if the internal friends list of the given user is either null
     * or empty. Designed to be used as a static method reference
     * ({@code UserCriteria::hasNoFriends}) within Stream predicates
     * </p>
     * @param user the {@link User} entity to be evaluated; must not be null
     * @return {@code true} if the user has no friends or if the friends list is uninitialized
     *         {@code false} otherwise
     */
    public static boolean hasNoFriends(User user) {
        return user.getFriends() == null || user.getFriends().isEmpty();
    }
}
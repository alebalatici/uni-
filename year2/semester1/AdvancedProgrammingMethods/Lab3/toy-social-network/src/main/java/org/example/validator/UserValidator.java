package org.example.validator;

import org.example.domain.User;

import java.time.LocalDate;

/**
 * Validator implementation for {@link User} entities
 * Ensures fields such as username, name, email, and birthdate satisfy domain requirements
 */
public class UserValidator implements Validator<User> {
    /**
     * Validates a {@link User} instance
     * <p>
     *     Checks that:
     * </p>
     * <ul>
     *     <li>
     *         User is not null
     *     </li>
     *     <li>
     *         Username is not empty and has at least 3 characters
     *     </li>
     *     <li>
     *         First and last names are not empty
     *     </li>
     *     <li>
     *         Email format is valid (contains '@' and '.')
     *     </li>
     *     <li>
     *         User is at least 13 years old
     *     </li>
     * </ul>
     * @param entity the entity {@link User} to validate
     * @throws ValidationException if any validation rule is violated
     */
    @Override
    public void validate(User entity) throws ValidationException {
        String errors = "";
        if (entity == null) {
            throw new IllegalArgumentException("User can't be null");
        }

        if (entity.getUsername() == null || entity.getUsername().trim().isEmpty()) {
            errors += "Username cannot be empty.\n";
        }

        else if (entity.getUsername().length() < 3) {
            errors += "Username must be at least 3 characters.\n";
        }

        if (entity.getFirstName() == null || entity.getFirstName().trim().isEmpty()) {
            errors += "First name cannot be empty.\n";
        }

        if (entity.getLastName() == null || entity.getLastName().trim().isEmpty()) {
            errors += "Last name cannot be empty.\n";
        }

        if (entity.getEmail() == null || !entity.getEmail().contains("@") || !entity.getEmail().contains(".")) {
            errors += "Email is invalid.\n";
        }

        if (entity.getBirthDate() == null || entity.getBirthDate().isAfter(LocalDate.now().minusYears(13))) {
            errors += "User must be at least 13 years old.\n";
        }

        if (!errors.isEmpty()) {
            throw new ValidationException(errors);
        }
    }
}
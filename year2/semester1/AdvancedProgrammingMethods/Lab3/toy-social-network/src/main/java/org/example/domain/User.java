package org.example.domain;
import java.time.LocalDate;

/**
 * Represents a user entity within the domain model
 * Extends {@link Entity} with a {@link Long} unique identifier
 */
public class User extends Entity<Long> {
    private String firstName;
    private String lastName;
    private String username;
    private String email;
    private String phoneNumber;
    private final LocalDate birthDate;

    /**
     * Constructs a {@code User} instance with an ID
     * @param id the unique identifier of the user
     * @param username the unique username
     * @param firstName the user's first name
     * @param lastName the user's last name
     * @param email the user's email adderss
     * @param birthDate the user's date of birth
     */
    public User(Long id, String username, String firstName, String lastName, String email, LocalDate birthDate) {
        this.setId(id);
        this.username = username;
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.birthDate = birthDate;
    }

    /**
     * Constructs a new {@code User} instance without ID
     * @param username the unique username
     * @param firstName the user's first name
     * @param lastName the user's last name
     * @param email the user's email address
     * @param birthDate the user's date of birth
     */
    public User(String username, String firstName, String lastName, String email, LocalDate birthDate) {
        this(null, username, firstName, lastName, email, birthDate);
    }

    /**
     * Gets the user's first name
     * @return the first name
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * Sets the user's first name
     * @param firstName the new first name
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /**
     * Gets the user's last name
     * @return the last name
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * Sets the user's last name
     * @param lastName the new last name
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    /**
     * Gets the user's username
     * @return the username
     */
    public String getUsername() {
        return username;
    }

    /**
     * Sets the user's username
     * @param username the new username
     */
    public void setUsername(String username) {
        this.username = username;
    }

    /**
     * Gets the user's email
     * @return the user's email
     */
    public String getEmail() {
        return email;
    }

    /**
     * Sets the user's email
     * @param email the new email
     */
    public void setEmail(String email) {
        this.email = email;
    }

    /**
     * Gets the user's phone number
     * @return the user's phone number
     */
    public String getPhoneNumber() {
        return phoneNumber;
    }

    /**
     * Sets the user's phone number
     * @param phoneNumber the user's phone number
     */
    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    /**
     * Gets the user's birthdate
     * @return the user's birthdate
     */
    public LocalDate getBirthDate() {
        return birthDate;
    }

    @Override
    public String toString() {
        return "User{" + "firstName=" + firstName + ", lastName=" + lastName + ", username=" + username + ", email=" + email + ", birthDate=" + birthDate.toString() + '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        return super.equals(o);
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }
}
package org.example.repo.database;

import org.example.domain.User;
import org.example.repo.Repository;
import org.example.repo.RepositoryException;
import org.example.validator.Validator;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * Database repository implementation for managing {@link User} entities
 * Provides CRUD operations backed by a relational database using JDBC
 */
public class UserDbRepository implements Repository<Long, User> {
    private final Validator<User> userValidator;
    private final String url;
    private final String username;
    private final String password;

    /**
     * Constructs a new {@code UserDbRepository} with the specified validator and database connection credentials
     * @param userValidator the validator used to verify {@link User} entities before persistence
     * @param url           the JDBC of the database
     * @param username      the database user on whose behalf the connection is being made
     * @param password      the user's password
     */
    public UserDbRepository(Validator<User> userValidator, String url, String username, String password) {
        this.userValidator = userValidator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    /**
     * Saves the given {@link User} entity to the database and assigns it the generated identifier
     * @param entity the user entity to be saved; must not be {@code null}
     * @return an empty {@link Optional} if the entity was successfully saved
     * @throws IllegalArgumentException if {@code entity} is {@code null}
     * @throws RuntimeException         if the entity fails validation
     * @throws RepositoryException      if a database access error occurs during insertion
     */
    @Override
    public Optional<User> save(User entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity is null");
        }

        userValidator.validate(entity);
        String sql = "INSERT INTO users (id, username, first_name, last_name, email, birth_date) VALUES (?, ?, ?, ?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            ps.setLong(1, entity.getId());
            ps.setString(2, entity.getUsername());
            ps.setString(3, entity.getFirstName());
            ps.setString(4, entity.getLastName());
            ps.setString(5, entity.getEmail());
            ps.setDate(6, Date.valueOf(entity.getBirthDate()));
            ps.executeUpdate();

            try (ResultSet keys = ps.getGeneratedKeys()) {
                keys.next();
                entity.setId(keys.getLong("id"));
            }
        } catch (SQLException e) {
            throw new RepositoryException("save user failed " + e.getMessage(), e);
        }

        return Optional.empty();
    }

    /**
     * Retrieves a {@link User} entity from the database by its unique identifier
     * @param id the identifier of the user to retrieve; must not be {@code null}
     * @return an {@link Optional} containing the found {@link User}, or {@link Optional#empty()} if no user exists with the given ID
     * @throws IllegalArgumentException if {@code id} is {@code null}
     * @throws RepositoryException      if a database access error occurs during the query
     */
    @Override
    public Optional<User> findOne(Long id) {
        if (id == null) {
            throw new IllegalArgumentException("id is null");
        }

        String sql = "SELECT * FROM users WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setLong(1, id);
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    User user = new User(resultSet.getString("username"),
                            resultSet.getString("first_name"),
                            resultSet.getString("last_name"),
                            resultSet.getString("email"),
                            resultSet.getDate("birth_date").toLocalDate());
                    user.setId(id);
                    return Optional.of(user);
                }
                return Optional.empty();
            }
        } catch (SQLException e) {
            throw new RepositoryException("findOne failed " + e.getMessage(), e);
        }
    }

    /**
     * Retrieves all {@link User} entities from the database, ordered ascending by their identifier
     * @return an {@link Iterable} containing all stored users (empty if none exist)
     * @throws RepositoryException if a database access error occurs during the query
     */
    @Override
    public Iterable<User> findAll() {
        List<User> users = new ArrayList<>();

        String sql = "SELECT * FROM users ORDER BY id";
        try (Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement statement = connection.prepareStatement(sql);
                ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String username = resultSet.getString("username");
                String firstName = resultSet.getString("first_name");
                String lastName = resultSet.getString("last_name");
                String email = resultSet.getString("email");
                LocalDate birthDate = resultSet.getDate("birth_date").toLocalDate();

                User user = new User(id, username, firstName, lastName, email, birthDate);
                user.setId(id);
                users.add(user);
            }
        } catch (SQLException e) {
            throw new RepositoryException("findAll failed " + e.getMessage(), e);
        }
        return users;
    }

    /**
     * Removes the {@link User} entity with the specified identifier from the database
     * @param id the identifier of the user to be deleted; must not be {@code null}
     * @return an {@link Optional} containing the deleted {@link User} if found and removed, or {@link Optional#empty()} if no user existed with the given ID
     * @throws IllegalArgumentException if {@code id} is {@code null}
     * @throws RepositoryException      if a database access error occurs during deletion
     */
    @Override
    public Optional<User> delete(Long id) {
        Optional<User> found = findOne(id);
        if (found.isPresent()) {
            return found;
        }

        String sql = "DELETE FROM users WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1, id);
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("delete user failed " + e.getMessage(), e);
        }
        return Optional.empty();
    }

    /**
     * Updates an existing {@link User} entity in the database
     * @param entity the user entity with updated fields; must not be {@code null}
     * @return an empty {@link Optional} if the user was successfully updated, or an {@link Optional} containing {@code entity} if no user with the given ID was found
     * @throws IllegalArgumentException if {@code entity} is {@code null}
     * @throws RuntimeException         if the entity fails validation
     * @throws RepositoryException      if a database access error occurs during the update
     */
    @Override
    public Optional<User> update(User entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity is null");
        }
        userValidator.validate(entity);

        String sql = "UPDATE users SET (username, first_name, last_name, email, birth_date) = (?, ?, ?, ?, ?) WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setString(1, entity.getUsername());
                ps.setString(2, entity.getFirstName());
                ps.setString(3, entity.getLastName());
                ps.setString(4, entity.getEmail());
                ps.setDate(5, Date.valueOf(entity.getBirthDate()));
                ps.setLong(6, entity.getId());
                int randuri = ps.executeUpdate();
                return randuri == 0 ? Optional.of(entity) : Optional.empty();
        } catch (SQLException e) {
            throw new RepositoryException("update user failed " + e.getMessage(), e);
        }
    }
}
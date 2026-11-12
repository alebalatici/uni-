package org.example;

import org.example.domain.User;
import org.example.repo.database.UserDbRepository;
import org.example.validator.UserValidator;
import org.junit.jupiter.api.BeforeEach;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class TestsRepoDatabase {
    private static final String URL = "jdbc:postgresql://localhost:5432/toy_social_network_test";
    private static final String USER = "postgres";
    private static final String PASSWORD = "postgres";

    private UserDbRepository userDbRepository;

    @BeforeEach
    void setup() throws SQLException {
        String sql = "TRUNCATE TABLE users RESTART IDENTITY CASCADE";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD)) {
            Statement statement = connection.createStatement();
            statement.executeUpdate(sql);
        }

        userDbRepository = new UserDbRepository(new UserValidator(), URL, USER, PASSWORD);
    }

    @Test
    void testSaveFindUpdateAndDelete() {
        List<User> users1 = new ArrayList<>();
        userDbRepository.findAll().forEach(users1::add);
        assertEquals(0, users1.size());

        // save
        User newUser = new User(1L, "test_user", "Test", "User", "test@gamil.com", LocalDate.of(2001, 6, 15));
        assertTrue(userDbRepository.save(newUser).isEmpty());
        assertNotNull(newUser.getId());
        assertEquals(1L, (long) newUser.getId());

        List<User> users2 = new ArrayList<>();
        userDbRepository.findAll().forEach(users2::add);
        assertEquals(1, users2.size());

        // find
        Optional<User> user = userDbRepository.findOne(1L);
        assertTrue(user.isPresent());
        assertEquals("test_user", user.get().getUsername());
        assertEquals("Test", user.get().getFirstName());
        assertEquals("User", user.get().getLastName());
        assertEquals("test@gamil.com", user.get().getEmail());
        assertEquals("2001-06-15", user.get().getBirthDate().toString());

        //update
        newUser.setFirstName("Updated");
        assertTrue(userDbRepository.update(newUser).isEmpty());
        assertEquals("Updated", userDbRepository.findOne(newUser.getId()).orElseThrow().getFirstName());
    }
}

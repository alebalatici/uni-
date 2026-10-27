package org.example.repo.file;

import org.example.domain.User;
import org.example.repo.RepositoryException;
import org.example.validator.Validator;

import java.time.LocalDate;

public class UserFileRepository extends AbstractFileRepository<Long, User> {
    public UserFileRepository(String fileName, Validator<User> validator) {
        super(fileName, validator);
    }

    @Override
    protected User extractEntity(String line) {
        String[] parts = line.split(";", -1);

        if (parts.length != 6) {
            System.err.println("Cannot extract user: " + line);
        }

        Long id = Long.parseLong(parts[0]);
        String username = parts[1];
        String firstName = parts[2];
        String lastName = parts[3];
        String email = parts[4];
        String dateString = parts[5];
        LocalDate date = LocalDate.parse(dateString);

        return new User(id, username, firstName, lastName, email, date);
    }

    @Override
    protected String createEntityAsString(User entity) {
        return entity.getId() + ";" + entity.getUsername() + ";" + entity.getFirstName() + ";" + entity.getLastName() + ";" + entity.getEmail() + ";" + entity.getBirthDate().toString();
    }
}
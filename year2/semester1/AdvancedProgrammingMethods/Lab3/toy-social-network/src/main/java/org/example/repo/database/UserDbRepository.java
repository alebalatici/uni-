package org.example.repo.database;

import org.example.domain.User;
import org.example.repo.Repository;
import org.example.validator.Validator;

public class UserDbRepository implements Repository<Long, User> {
    private final Validator<User> userValidator;
    private final String url;
    private final String username;
    private final String password;

    public UserDbRepository(Validator<User> userValidator, String url, String username, String password) {
        this.userValidator = userValidator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public User save(User entity) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public User find(Long aLong) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Iterable<User> findAll() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public User delete(Long aLong) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public User update(User entity) {
        throw new UnsupportedOperationException("Not supported yet.");
    }
}
package org.example.repo.database;

import org.example.domain.Friendship;
import org.example.domain.Tuple;
import org.example.repo.Repository;
import org.example.validator.Validator;

import java.util.Optional;

public class FriendshipDbRepository implements Repository<Tuple<Long, Long>, Friendship> {
    private final Validator<Friendship> friendshipValidator;
    private final String url;
    private final String username;
    private final String password;

    public FriendshipDbRepository(Validator<Friendship> friendshipValidator, String url, String username, String password) {
        this.friendshipValidator = friendshipValidator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Friendship> save(Friendship entity) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Optional<Friendship> findOne(Tuple<Long, Long> longLongTuple) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Iterable<Friendship> findAll() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Optional<Friendship> delete(Tuple<Long, Long> longLongTuple) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Optional<Friendship> update(Friendship entity) {
        throw new UnsupportedOperationException("Not supported yet.");
    }
}
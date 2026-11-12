package org.example.repo.file;

import org.example.domain.Friendship;
import org.example.domain.Tuple;
import org.example.domain.User;
import org.example.repo.RepositoryException;
import org.example.validator.Validator;


import java.time.LocalDateTime;

public class FriendshipFileRepository extends AbstractFileRepository<Tuple<Long, Long>, Friendship> {
    public FriendshipFileRepository(String fileName, Validator<Friendship> validator) {
        super(fileName, validator);
    }

    @Override
    protected Friendship extractEntity(String line) {
        String[] parts = line.split(";", -1);

        if (parts.length != 3) {
            System.err.println("Cannot extract friendship from file: " + line);
        }

        Long idUser1 = Long.parseLong(parts[0]);
        Long idUser2 = Long.parseLong(parts[1]);
        String dateString = parts[2];
        LocalDateTime date = LocalDateTime.parse(dateString);

        return new Friendship(idUser1, idUser2, date);
    }

    @Override
    protected String createEntityAsString(Friendship entity) {
        return entity.getIdUser1() + ";" + entity.getIdUser2() + ";" + entity.getFriendsFrom().toString();
    }
}
package org.example.validator;

import org.example.domain.Friendship;

/**
 * Validator implementation for {@link Friendship} entities
 * Ensures fields such as idUser1 and idUser2 satisfy domain requirements
 */
public class FriendshipValidator implements Validator<Friendship> {
    /**
     * Validates a {@link Friendship} instance
     * <p>
     *     Checks that:
     * </p>
     * <ul>
     *     <li>
     *         Friendship is not null
     *     </li>
     *     <li>
     *         idUser1 and idUser2 are not null
     *     </li>
     *     <li>
     *         The friendship is created between 2 user ids
     *     </li>
     * </ul>
     * @param entity the entity {@link Friendship} to validate
     * @throws ValidationException if any validation rule is violated
     */
    @Override
    public void validate(Friendship entity) throws ValidationException {
        if (entity == null) {
            throw new ValidationException("Friendship can't be null");
        }

        if (entity.getIdUser1() == null || entity.getIdUser2() == null) {
            throw new ValidationException("Friendships can't be between null id's");
        }

        if (entity.getIdUser1().equals(entity.getIdUser2())) {
            throw new ValidationException("Friendships can't be the same id's");
        }
    }
}
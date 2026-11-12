package org.example.domain;
import java.time.LocalDateTime;

/**
 * Represents a friendship relationship between two users in the domain model
 * Extends {@link Entity} with a composite key represented by a {@link Tuple} of user IDs
 */
public class Friendship extends Entity<Tuple<Long, Long>> {
    private final LocalDateTime friendsFrom;

    /**
     * Constructs a {@code Friendship} with explicit IDs and timestamp
     * User primarily for Jackson JSON deserialization or persistence mapping
     * @param idUser1 the ID of the first user
     * @param idUser2 the ID of the second user
     * @param friendsFrom the date and time when the friendship was established
     */
    public Friendship(Long idUser1, Long idUser2, LocalDateTime friendsFrom) {
        if (idUser1 != null && idUser2 != null && idUser1 > idUser2) {
            setId(new Tuple<>(idUser2, idUser1));
        }
        else {
            setId(new Tuple<>(idUser1, idUser2));
        }
        this.friendsFrom = friendsFrom;
    }

    /**
     * Constructs a new {@code Friendship} with the current date and time
     * @param idUser1 the ID of the first user
     * @param idUser2 the ID of the second user
     */
    public Friendship(Long idUser1, Long idUser2) {
        this(idUser1, idUser2, LocalDateTime.now());
    }

    /**
     * Gets the id of the first user in the friendship
     * @return the first user ID form the tuple ID, or the field value if the ID tuple is null
     */
    public Long getIdUser1() {
        return this.getId().getLeft();
    }

    /**
     * Gets the ID of the second user in the friendship
     * @return the second user ID from the tuple ID, or the field value if the ID tuple is null
     */
    public Long getIdUser2() {
        return this.getId().getRight();
    }

    /**
     * Gets the date and time when the friendship was created
     * @return the timestamp of when the friendship started
     */
    public LocalDateTime getFriendsFrom() {
        return friendsFrom;
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

    @Override
    public String toString() {
        return "Friendship{" + "idUser1=" + getIdUser1() + ", idUser2=" + getIdUser2() + ", friendsFrom=" + friendsFrom + '}';
    }
}
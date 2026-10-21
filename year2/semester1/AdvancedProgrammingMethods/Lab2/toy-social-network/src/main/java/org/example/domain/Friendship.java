package org.example.domain;

import com.fasterxml.jackson.annotation.JsonCreator;
import com.fasterxml.jackson.annotation.JsonProperty;

import java.time.LocalDateTime;

/**
 * Represents a friendship relationship between two users in the domain model
 * Extends {@link Entity} with a composite key represented by a {@link Tuple} of user IDs
 */
public class Friendship extends Entity<Tuple<Long, Long>> {
    private final Long idUser1;
    private final Long idUser2;
    private final LocalDateTime friendsFrom;

    /**
     * Constructs a {@code Friendship} with explicit IDs and timestamp
     * User primarily for Jackson JSON deserialization or persistence mapping
     * @param idUser1 the ID of the first user
     * @param idUser2 the ID of the second user
     * @param friendsFrom the date and time when the friendship was established
     */
    @JsonCreator
    public Friendship(
            @JsonProperty("idUser1") Long idUser1,
            @JsonProperty("idUser2") Long idUser2,
            @JsonProperty("friendsFrom") LocalDateTime friendsFrom) {
        this.idUser1 = idUser1;
        this.idUser2 = idUser2;
        this.friendsFrom = friendsFrom;
        this.setId(new Tuple<>(idUser1, idUser2));
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
        if (this.getId() != null) {
            return this.getId().getLeft();
        }

        return this.idUser1;
    }

    /**
     * Gets the ID of the second user in the friendship
     * @return the second user ID from the tuple ID, or the field value if the ID tuple is null
     */
    public Long getIdUser2() {
        if (this.getId() != null) {
            return this.getId().getRight();
        }

        return this.idUser2;
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
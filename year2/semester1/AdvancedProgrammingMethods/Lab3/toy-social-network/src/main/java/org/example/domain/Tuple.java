package org.example.domain;

import java.io.Serial;
import java.io.Serializable;
import java.util.Objects;

/**
 * Represents a generic pair of two related elements
 * @param <E1> the type of the first (left) element
 * @param <E2> the type of the second (right) element
 */
public class Tuple<E1 extends Comparable<E1>, E2 extends Comparable<E2>> implements Serializable {
    @Serial
    private static final long serialVersionUID = 1L;

    private E1 left;
    private E2 right;

    /**
     * Constructs an empty {@code Tuple}
     */
    public Tuple() {

    }

    /**
     * Constructs a {@code Tuple} with the specified left and right elements
     * @param left the first element
     * @param right the second element
     */
    public Tuple(E1 left,E2 right) {
        this.left = left;
        this.right = right;
    }

    /**
     * Gets the left element of the tuple
     * @return the left element
     */
    public E1 getLeft() {
        return left;
    }

    /**
     * Sets the left element of the tuple
     * @param left the new left element
     */
    public void setLeft(E1 left) {
        this.left = left;
    }

    /**
     * Gets the right element of the tuple
     * @return the right element
     */
    public E2 getRight() {
        return right;
    }

    /**
     * Sets the right element of the tuple
     * @param right the new right element
     */
    public void setRight(E2 right) {
        this.right = right;
    }

    /**
     * Compares this tuple with another object for equality
     * <p>
     *     Two tuples are considered equal if their elements match regardless of position
     * </p>
     * @param o   the reference object with which to compare.
     * @return {@code true} if the objects are equal under symmetric pair logic; {@code false} otherwise
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Tuple<?, ?> tuple = (Tuple<?, ?>) o;
        return (Objects.equals(left, tuple.left) && Objects.equals(right, tuple.right)) ||
                Objects.equals(left, tuple.right) && Objects.equals(right, tuple.left);
    }

    /**
     * Computes a symmetric hash code for this tuple
     * <p>
     *     Ensures that {@code Tuple(A, B)} produces the same hash code as {@code Tuple(B, A)} maintaining consistency with {@link #equals(Object)}
     * </p>
     * @return the symmetric hash code value for this tuple
     */
    @Override
    public int hashCode() {
        return Objects.hash(left, right) + Objects.hash(right, left);
    }
}
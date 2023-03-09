package domain;

import java.io.Serial;
import java.io.Serializable;

/**
 * Class that represents an entity.
 * @param <ID> the type of the id of the entity
 */
public class Entity<ID> implements Serializable, Deletable {

    @Serial
    private static final long serialVersionUID = 7331115341259248461L;
    private ID id;

    private boolean isDeleted = false;

    /**
     * Checks if the entity is deleted
     * @return true if the entity is deleted, false otherwise
     */
    public boolean isDeleted() {
        return isDeleted;
    }

    /**
     * Sets the deleted flag to true or false
     * @param deleted the new value of the deleted flag
     */
    public void setDeleted(boolean deleted) {
        isDeleted = deleted;
    }

    public ID getId() {
        return id;
    }

    public void setId(ID id) {
        this.id = id;
    }
}
package domain.factory;

import domain.Entity;

import java.util.List;

public interface Factory<ID, E extends Entity<ID>> {

    /**
     * Creates an entity of type E
     * @param strategy the type of the entity
     * @param attributes the attributes of the entity
     * @return the entity
     */
    E createEntity(Class<E> strategy ,List<String> attributes);
}

package domain.factory;

import domain.Entity;
import java.util.List;

public class EntityFactory<ID, E extends Entity<ID>> implements Factory<ID, E> {

    private static EntityFactory singleton = null;

    private EntityFactory() {
    }

    public synchronized static EntityFactory getInstance() {
        if (singleton == null) {
            singleton = new EntityFactory();
        }
        return singleton;
    }

    @Override
    public E createEntity(Class<E> strategy, List<String> attributes) {

        return null;
    }
}

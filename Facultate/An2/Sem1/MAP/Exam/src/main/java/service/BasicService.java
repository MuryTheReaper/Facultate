package service;

import domain.Entity;
import domain.factory.EntityFactory;
import repository.Repository;

import java.util.Collection;
import java.util.List;

public abstract class BasicService<ID, E extends Entity<ID>> implements Service<ID, E> {

    private final Repository<ID, E> repository;

    public BasicService(Repository<ID, E> repository) {
        this.repository = repository;
    }

    /**
     * Creates a new entity from the given parameters.
     * @param attributes the parameters used to create the entity.
     * @return the created entity.
     */
    private E createEntity(List<String> attributes) {
        EntityFactory<ID, E> factory = EntityFactory.getInstance();
        return factory.createEntity(repository.getEntityClass(), attributes);
    }

    @Override
    public E findOne(ID id) {
        return repository.findOne(id);
    }

    @Override
    public Iterable<E> findAll() {
        return repository.findAll();
    }

    @Override
    public Iterable<E> findTrueAll() {
        return repository.findTrueAll();
    }

    @Override
    public E save(List<String> attributes) {
        E entity = createEntity(attributes);
        if(entity.getId() == null)
            entity.setId(getNextId());
        else
            entity.setDeleted(true);
        return repository.save(entity);
    }

    @Override
    public E delete(ID id) {
        return repository.delete(id);
    }

    @Override
    public E update(List<String> attributes) {
        E entity = createEntity(attributes);
        return repository.update(entity);
    }

    public abstract ID getNextId();

}

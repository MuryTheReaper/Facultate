package service;

import domain.Entity;

import java.util.List;

public interface Service<ID, E extends Entity<ID>>{

        /**
         * Finds an entity by its id
         * @param id - must not be null
         * @return an entity with the given id or null if there is no entity with the given id
         */
        E findOne(ID id);

        /**
         *
         * @return all entities
         */
        Iterable<E> findAll();


        Iterable<E> findTrueAll();

        /**
         * Saves an entity
         * @param attributes - must not be null
         * @return null - if the given entity is saved otherwise returns the entity (id already exists)
         */
        E save(List<String> attributes);

        /**
         * Deletes an entity with the given id
         * @param id - must not be null
         * @return the deleted entity or null if there is no entity with the given id
         */
        E delete(ID id);

        /**
         * Updates an entity
         * @param attributes - must not be null
         * @return null - if the entity is updated, otherwise returns the entity (e.g id does not exist).
         */
        E update(List<String> attributes);

        /**
         * Generates the next valid id
         * @return the next valid id
         */
        ID getNextId();
}

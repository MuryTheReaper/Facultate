package repo;

public interface Repository<E, ID> {
    E save(E entity) throws ValidatorException;
    E delete(ID id);
    E findOne(ID id);
    Iterable<E> findAll();
}

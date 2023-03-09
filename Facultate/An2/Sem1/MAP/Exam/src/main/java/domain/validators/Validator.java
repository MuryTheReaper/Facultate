package domain.validators;

public interface Validator <T> {
    /**
     * Validates an entity.
     * @param entity - must not be null
     * @throws ValidatorException - if the entity is not valid
     */
    void validate(T entity) throws ValidatorException;
}

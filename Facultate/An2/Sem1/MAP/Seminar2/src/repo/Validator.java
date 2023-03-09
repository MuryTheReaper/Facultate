package repo;

public interface Validator<T> {
    void validate(T entry) throws ValidatorException;
}

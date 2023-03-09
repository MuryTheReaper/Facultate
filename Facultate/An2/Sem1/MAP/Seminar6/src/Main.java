import domain.User;
import repository.Repository;
import repository.UserDBRepository;

public class Main {
    public static void main(String[] args) {

        String url = "jdbc:postgresql://localhost:5432/test";
        Repository<Long, User> userDBRepository = new UserDBRepository(url, "postgres", "postgres");

        userDBRepository.findAll().forEach(System.out::println);
    }
}
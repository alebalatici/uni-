import org.example.console.Console;
import org.example.domain.Friendship;
import org.example.domain.Tuple;
import org.example.domain.User;
import org.example.repo.*;
import org.example.repo.factory.RepositoryFactory;
import org.example.service.NetworkService;
import org.example.validator.FriendshipValidator;
import org.example.validator.UserValidator;
import org.example.validator.Validator;

public class Main {
    static void main() {
        Validator<User> userValidator = new UserValidator();
        Validator<Friendship> friendshipValidator = new FriendshipValidator();

        RepositoryFactory repositoryFactory = new  RepositoryFactory();

        Repository<Long, User> userRepository = repositoryFactory.createUserRepository(userValidator);
        Repository<Tuple<Long, Long>, Friendship> friendshipRepository = repositoryFactory.createFriendshipRepository(friendshipValidator);
        NetworkService networkService = new NetworkService(userRepository, friendshipRepository, userValidator, friendshipValidator);
        Console console = new Console(networkService);
        console.run();
    }
}
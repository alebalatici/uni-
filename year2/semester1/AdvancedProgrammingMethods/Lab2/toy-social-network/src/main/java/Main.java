import org.example.console.Console;
import org.example.domain.Friendship;
import org.example.domain.Tuple;
import org.example.domain.User;
import org.example.repo.FriendshipRepository;
import org.example.repo.Repository;
import org.example.repo.UserRepository;
import org.example.service.NetworkService;
import org.example.validator.FriendshipValidator;
import org.example.validator.UserValidator;
import org.example.validator.Validator;

public class Main {
    static void main() {
        Repository<Long, User> userRepository = new UserRepository("data/users.json");
        Repository<Tuple<Long, Long>, Friendship> friendshipRepository = new FriendshipRepository("data/friendships.json");
        Validator<User> userValidator = new UserValidator();
        Validator<Friendship> friendshipValidator = new FriendshipValidator();
        NetworkService networkService = new NetworkService(userRepository, friendshipRepository, userValidator, friendshipValidator);
        Console console = new Console(networkService);
        console.run();
    }
}
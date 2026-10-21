package org.example.console;

import org.example.domain.Friendship;
import org.example.domain.User;
import org.example.service.NetworkService;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Scanner;

/**
 * Text-based user interface (Console) for managing network users and friendships
 * Handles user input, menu rendering, and delegates operation to {@link NetworkService}
 */
public class Console {
    private final NetworkService networkService;
    private final Scanner scanner;
    private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd");

    /**
     * Constructs a {@code Console} interface with the specified network service
     * @param networkService the business logic service managing the network
     */
    public Console(NetworkService networkService) {
        this.networkService = networkService;
        this.scanner = new Scanner(System.in);
    }

    private void printMenu() {
        System.out.println("Menu");
        System.out.println("1. Add User");
        System.out.println("2. Remove User");
        System.out.println("3. Add Friendship");
        System.out.println("4. Remove Friendship");
        System.out.println("5. Print the number of comunities");
        System.out.println("6. Print the most sociable comunity");
        System.out.println("7. Print all the users");
        System.out.println("8. Print all the friendships");
        System.out.println("9. Exit");
    }

    private int readInt(String message) {
        while (true) {
            System.out.print(message);
            if (scanner.hasNextInt()) {
                int value = scanner.nextInt();
                scanner.nextLine();
                return value;
            }

            System.out.println("Invalid input. Please try again.");
            scanner.next();
        }
    }

    /**
     * Displays the main menu and starts the interactive console loop
     */
    public void run() {
        while (true) {
            printMenu();
            int option = readInt(">>>");

            switch (option) {
                case 1 -> addUserUi();
                case 2 -> removeUserUi();
                case 3 -> addFriendshipUi();
                case 4 -> removeFriendshipUi();
                case 5 -> printTheNumberOfComunities();
                case 6 -> printTheMostSociableComunity();
                case 7 -> printAllUsers(networkService.getAllUsers());
                case 8 -> printAllFriendships(networkService.getAllFriendships());
                case 9 -> {
                    System.out.println("Exiting the application...");
                    return;
                }
                default -> {
                    System.out.println("Invalid input. Please try again.");
                }
            }
        }
    }

    private void addUserUi() {
        try {
            System.out.print("ID: ");
            Long id = Long.parseLong(scanner.nextLine().trim());

            System.out.print("Username: ");
            String username = scanner.nextLine().trim();

            System.out.print("First Name: ");
            String firstName = scanner.nextLine().trim();

            System.out.print("Last Name: ");
            String lastName = scanner.nextLine().trim();

            System.out.print("Email: ");
            String email = scanner.nextLine().trim();

            System.out.print("Date of Birth (YYYY-MM-DD): ");
            LocalDate birthDate = LocalDate.parse(scanner.nextLine().trim(), DATE_FORMATTER);

            networkService.addUser(id, username, firstName, lastName, email, birthDate);
            System.out.println("User has been added successfully!");
        }

        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private void addFriendshipUi() {
        try {
            System.out.print("First ID: ");
            Long id1 = Long.parseLong(scanner.nextLine().trim());

            System.out.print("Second ID: ");
            Long id2 = Long.parseLong(scanner.nextLine().trim());

            System.out.print("Do you want to specify a custom start date for this friendship? (y/N): ");
            String choice = scanner.nextLine().trim().toLowerCase();

            if (choice.equals("y") || choice.equals("yes")) {
                System.out.print("Enter date and time (yyyy-MM-dd HH:mm): ");
                String dateInput = scanner.nextLine().trim();

                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
                LocalDateTime friendsFrom = LocalDateTime.parse(dateInput, formatter);

                networkService.addFriendship(id1, id2, friendsFrom);
            }

            else {
                networkService.addFriendship(id1, id2);
            }
            System.out.println("Friendship has been added successfully!");
        }

        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private void removeFriendshipUi() {
        try {
            System.out.print("First ID: ");
            Long id1 = Long.parseLong(scanner.nextLine().trim());

            System.out.print("Second ID: ");
            Long id2 = Long.parseLong(scanner.nextLine().trim());

            networkService.removeFriendship(id1, id2);
        }

        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private void removeUserUi() {
        try {
            System.out.print("ID: ");
            Long id = Long.parseLong(scanner.nextLine().trim());

            networkService.removeUser(id);
            System.out.println("User has been removed successfully!");
        }

        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private void printAllUsers(List<User> users) {
        if (users.isEmpty()) {
            System.out.println("No users have been added!");
        }

        else {
            users.forEach(System.out::println);
        }
    }

    private void printAllFriendships(List<Friendship> friendships) {
        if (friendships.isEmpty()) {
            System.out.println("No friendships have been added!");
        }

        else {
            friendships.forEach(System.out::println);
        }
    }

    public void printTheNumberOfComunities() {
        try {
            System.out.println("The total number of comunities: " + networkService.getNumberOfComunities());
        }

        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public void printTheMostSociableComunity() {
        try {
            List<User> users = networkService.getMostSociableComunity();
            System.out.println("The most sociable comunity consists of: ");
            for (User user : users) {
                System.out.println(user.getUsername());
            }
        }

        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
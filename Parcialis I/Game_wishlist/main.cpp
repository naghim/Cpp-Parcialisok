#include "game.h"
#include "user.h"

#include <fstream>

int main() {
    // Read user data from user.txt
    User user;
    std::ifstream input("user.txt");

    input >> user;
    std::cout << user << std::endl;

    // Add new game
    Game game("Dota 2", 0.00);
    user.addToWishlist(game);

    try {
        user.addToWishlist(game);
        throw std::runtime_error("Failed to raise exception during add.");
    } catch (std::invalid_argument& e) {
        std::cout << "Successfully prevented adding duplicate game." << std::endl;
    }

    // Remove game
    user.removeFromWishlist("Doesn't Exist");
    user.removeFromWishlist("Valorant");

    std::cout << "After removing Valorant:" << std::endl;
    std::cout << user << std::endl;

    // Test sorting
    user.sortWishlistBy(SortOption::BY_PRICE);
    std::cout << "After sorting by price:" << std::endl;
    std::cout << user << std::endl;

    user.sortWishlistBy(SortOption::BY_TITLE);
    std::cout << "After sorting by title:" << std::endl;
    std::cout << user << std::endl;

    // Test copy
    std::cout << "Game title: " << game.getTitle() << std::endl;

    Game game2 = game;
    Game game3(game);
    std::cout << "Game 2 title: " << game2.getTitle() << std::endl;
    std::cout << "Game 3 title: " << game3.getTitle() << std::endl;

    // Test move
    Game game4 = std::move(game);
    Game game5(std::move(game2));
    std::cout << "Game 4 title: " << game4.getTitle() << std::endl;
    std::cout << "Game 5 title: " << game5.getTitle() << std::endl;

    return 0;
}
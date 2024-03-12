#ifndef USER_H
#define USER_H

#include "game.h"

#include <iostream>
#include <vector>
#include <string>

// Enum for sorting options
enum SortOption {
    BY_TITLE,
    BY_PRICE
};

class User {
public:
    // Constructors
    User();
    User(const std::string &username);
    User(const User &other);
    User(User &&other);

    // Assignment operators
    User& operator=(const User &other);
    User& operator=(User &&other); 

    // Getter methods
    std::string getUsername() const;

    // Wishlist management
    void addToWishlist(const Game &game);
    void removeFromWishlist(const std::string &gameTitle);

    // Sort wishlist by name or price
    void sortWishlistBy(SortOption option);

    // Inserter operator
    friend std::ostream& operator<<(std::ostream &os, const User &user);

    // Extractor operator
    friend std::istream& operator>>(std::istream &is, User &user);

private:
    std::string username;
    std::vector<Game> wishlist;
};

#endif
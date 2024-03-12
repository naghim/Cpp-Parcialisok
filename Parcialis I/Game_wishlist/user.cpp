#include "user.h"

#include <algorithm>

User::User() {
    this->username = "";
}

User::User(const std::string& username) {
    this->username = username;
}

// Copy constructor
User::User(const User& other) {
    this->username = other.username;
    this->wishlist = other.wishlist;
}

// Move constructor
User::User(User&& other) {
    this->username = other.username;
    this->wishlist = other.wishlist;

    other.username.clear();
    other.wishlist.clear();
}

// Copy assignment
User& User::operator=(const User& other) {
    if (this != &other) {
        this->username = other.username;
        this->wishlist = other.wishlist;
    }
    return *this;

}

// Move assignment
User& User::operator=(User&& other) {
    if (this != &other) {
        this->username = other.username;
        this->wishlist = other.wishlist;
        
        other.username.clear();
        other.wishlist.clear();
    }

    return *this;
}

// Getter method
std::string User::getUsername() const {
    return this->username;
}

// Wishlist management
void User::addToWishlist(const Game& game) {
    if (std::find(this->wishlist.begin(), this->wishlist.end(), game) == this->wishlist.end()) {
        this->wishlist.push_back(game);
    } else {
        throw std::invalid_argument("Game already in wishlist");
    }
}

void User::removeFromWishlist(const std::string& gameTitle) {
    auto it = std::find_if(this->wishlist.begin(), this->wishlist.end(), [&gameTitle](const Game& game) {
        return game.getTitle() == gameTitle;
    });

    if (it != this->wishlist.end()) {
        this->wishlist.erase(it);
    }
}

// Sort wishlist by name or price
void User::sortWishlistBy(SortOption option) {
    switch (option) {
        case SortOption::BY_TITLE:
            std::sort(this->wishlist.begin(), this->wishlist.end(), [](const Game& game1, const Game& game2) {
                return game1.getTitle() < game2.getTitle();
            });
            break;
        case SortOption::BY_PRICE:
            std::sort(this->wishlist.begin(), this->wishlist.end(), [](const Game& game1, const Game& game2) {
                return game1.getPrice() < game2.getPrice();
            });
            break;
    }
}

// Inserter operator
std::ostream& operator<<(std::ostream& os, const User& user) {
    os << user.username << std::endl;
    os << user.wishlist.size() << std::endl;

    for (const Game& game : user.wishlist) {
        os << game;
    }

    return os;
}

// Extractor operator
std::istream& operator>>(std::istream &is, User &user) {
    is >> user.username;

    int wishlistSize;
    is >> wishlistSize;

    for (int i = 0; i < wishlistSize; i++) {
        Game game;
        is >> game;

        user.wishlist.push_back(game);
    }

    return is;
}
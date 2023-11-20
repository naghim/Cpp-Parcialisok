#include "Game.h"
#include <iostream>
#include <string>

Game::Game() {
    this->title = "";
    this->price = 0.0;
}

Game::Game(const std::string& title, double price) {
    this->title = title;
    this->price = price;
}

// Copy constructor
Game::Game(const Game& other) {
    this->title = other.title;
    this->price = other.price;
}

// Move constructor
Game::Game(Game&& other) {
    this->title = other.title;
    this->price = other.price;

    other.title.clear();
    other.price = 0.0;
}

// Copy assignment operator
Game& Game::operator=(const Game& other) {
    if (this != &other) {
        this->title = other.title;
        this->price = other.price;
    }

    return *this;
}


// Move assignment
Game& Game::operator=(Game&& other) {
    if (this != &other) {
        this->title = other.title;
        this->price = other.price;
        
        other.title.clear();
        other.price = 0.0;
    }

    return *this;
}

// Getter methods
std::string Game::getTitle() const {
    return this->title;
}
double Game::getPrice() const {
    return this->price;
}

// Equality operator overloading
bool Game::operator==(const Game& other) {
    return this->title == other.title;
}

// Inserter operator
std::ostream& operator<<(std::ostream& os, const Game& game) {
    os << game.title << ": " << game.price << std::endl;
    return os;
}

// Extractor operator
std::istream& operator>>(std::istream &is, Game &game) {
    is >> game.title >> game.price;
    return is;
}
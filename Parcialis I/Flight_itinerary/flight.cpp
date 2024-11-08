#include "flight.h"

// Konstruktorok
Flight::Flight() : departure(""), destination(""), price(0.0), popularity(0.0) {}

Flight::Flight(const std::string &departure, const std::string &destination, double price, double popularity)
    : departure(departure), destination(destination), price(price), popularity(popularity) {}

Flight::Flight(const Flight &other)
    : departure(other.departure), destination(other.destination), price(other.price), popularity(other.popularity) {}

Flight::Flight(Flight &&other)
    : departure(std::move(other.departure)), destination(std::move(other.destination)), price(other.price), popularity(other.popularity) {
    other.price = 0.0;
    other.popularity = 0.0;
}

// Értékadás operátorok
Flight& Flight::operator=(const Flight &other) {
    if (this != &other) {
        departure = other.departure;
        destination = other.destination;
        price = other.price;
        popularity = other.popularity;
    }

    return *this;
}

Flight& Flight::operator=(Flight &&other) {
    if (this != &other) {
        departure = std::move(other.departure);
        destination = std::move(other.destination);
        price = other.price;
        popularity = other.popularity;
        other.price = 0.0;
        other.popularity = 0.0;
    }

    return *this;
}

// Getterek
std::string Flight::getDeparture() const {
    return departure;
}

std::string Flight::getDestination() const {
    return destination;
}

double Flight::getPrice() const {
    return price;
}

double Flight::getPopularity() const {
    return popularity;
}

// Egyenlőség operátor
bool Flight::operator==(const Flight &other) const {
    return departure == other.departure && destination == other.destination && price == other.price && popularity == other.popularity;
}

// << operátor
std::ostream& operator<<(std::ostream &os, const Flight &flight) {
    os << "Departure: " << flight.departure << ", Destination: " << flight.destination
       << ", Price: " << flight.price << ", Popularity: " << flight.popularity;

    return os;
}

// >> operátor
std::istream& operator>>(std::istream &is, Flight &flight) {
    is >> flight.departure >> flight.destination >> flight.price >> flight.popularity;

    return is;
}
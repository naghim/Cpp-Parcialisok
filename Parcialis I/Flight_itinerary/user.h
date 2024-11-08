#ifndef USER_H
#define USER_H

#include <vector>
#include "flight.h"

class User {
public:
    // Konstruktorok
    User();
    User(const std::string &name);
    User(const User &other);
    User(User &&other);

    // Értékadás operátorok
    User& operator=(const User &other);
    User& operator=(User &&other);

    // Getter
    std::string getName() const;

    // Repülések kezelése

    // Egy új járat hozzáadása a tervhez
    // Dobjon std::invalid_argument kivételt, ha a járat már szerepel a tervben
    // Növeljuk a járat népszerűségét 1-el, mikor bekerül a tervbe
    void addToItinerary(const Flight &flight);

    // Egy járat eltávolítása a tervből
    // Dobjon kivételt, ha a járat nem szerepel a tervben
    // Csökkentjük a járat népszerűségét 1-el, mikor kikerül a tervből
    void removeFromItinerary(const std::string &departure, const std::string &destination);

    // A tervben szereplő járatok rendezése népszerűség szerint, csökkenő sorrendben
    void sortItineraryByPopularity();

    // A minPopularity-nál kisebb népszerűségű járatok törlése a tervből
    void removeUnpopularFlights(double minPopularity);

    // << operátor
    // A felhasználó nevét és a tervben szereplő járatokat írja ki
    // Használd a Flight osztály operátorát a járatok kiírásához
    friend std::ostream& operator<<(std::ostream &os, const User &user);
    
    // >> operátor
    // A felhasználó nevét és a repülések számát (n), majd a tervben szereplő járatokat olvassa be 
    // Használd a Flight osztály operátorát a járatok beolvasásához
    friend std::istream& operator>>(std::istream &is, User &user);

private:
    std::string name;
    std::vector<Flight> itinerary;
};

#endif
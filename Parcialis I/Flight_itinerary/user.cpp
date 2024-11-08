#include "user.h"
#include <algorithm>
#include <stdexcept>

// Konstruktorok
User::User() : name("") {}

User::User(const std::string &name) : name(name) {}

User::User(const User &other) : name(other.name), itinerary(other.itinerary) {}

User::User(User &&other) : name(std::move(other.name)), itinerary(std::move(other.itinerary)) {}

// Értékadás operátorok
User& User::operator=(const User &other) {
    if (this != &other) {
        name = other.name;
        itinerary = other.itinerary;
    }

    return *this;
}

User& User::operator=(User &&other) {
    if (this != &other) {
        name = std::move(other.name);
        itinerary = std::move(other.itinerary);
    }

    return *this;
}

// Getter
std::string User::getName() const {
    return name;
}

// Repülések kezelése
void User::addToItinerary(const Flight &flight) {
    for (const auto &f : itinerary) {
        if (f == flight) {
            throw std::invalid_argument("Flight already in itinerary");
        }
    }

    itinerary.push_back(flight);
}

void User::removeFromItinerary(const std::string &departure, const std::string &destination) {
    auto it = std::find_if(itinerary.begin(), itinerary.end(), [&](const Flight &f) {
        return f.getDeparture() == departure && f.getDestination() == destination;
    });

    if (it == itinerary.end()) {
        throw std::invalid_argument("Flight not found in itinerary");
    }

    itinerary.erase(it);
}

void User::sortItineraryByPopularity() {
    std::sort(itinerary.begin(), itinerary.end(), [](const Flight &a, const Flight &b) {
        return a.getPopularity() > b.getPopularity();
    });
}

void User::removeUnpopularFlights(double minPopularity) {
    itinerary.erase(std::remove_if(itinerary.begin(), itinerary.end(), [minPopularity](const Flight &f) {
        return f.getPopularity() < minPopularity;
    }), itinerary.end());
}

/*
Q: Miért nem jó a removeUnpopularFlights implementációja for ciklusokkal?
Pl.:

for (int i = 0; i < itinerary.size(); ++i) {
    if (itinerary[i].getPopularity() < minPopularity) {
        itinerary.erase(itinerary.begin() + i);
    }
}

A for ciklusokkal való implementáció azért nem jó, mert az erase() metódus meghívásakor az i. elem törlődik,
és az i+1-dik elem a régi i pozícióra kerül. Emiatt újra kellene ellenőrizni még egyszer az i. pozíciót (ami nem történik meg), és már csak (n - 1)-ig kellene tartson a for ciklus. Ezt hívjuk off-by-one hibának.

Ugyanez a hiba előáll, ha új típusú for ciklust használunk:

for (const auto &flight : itinerary) {
    if (flight.getPopularity() < minPopularity) {
        auto occurrence = std::find(itinerary.begin(), itinerary.end(), flight);

        if (occurrence != itinerary.end()) {
            itinerary.erase(occurrence);
        }
    }
}

Sima int/új típusú for helyett iterátorral is végig lehet menni a vektoron, így nem lesz hiba, 
mivel az iterátorok frissítik magukat egy-egy törlés után a helyes pozícióra:

for (auto it = itinerary.begin(); it != itinerary.end(); ) {
    if (it->getPopularity() < minPopularity) {
        it = itinerary.erase(it);
    } else {
        ++it;
    }
}
*/

// << operátor
std::ostream& operator<<(std::ostream &os, const User &user) {
    os << "Name: " << user.name << "\nItinerary:\n";

    for (const auto &flight : user.itinerary) {
        os << " - " << flight << "\n";
    }

    return os;
}

// >> operátor
std::istream& operator>>(std::istream &is, User &user) {
    int n;
    Flight flight;

    is >> user.name >> n;

    for (int i = 0; i < n; ++i) {
        is >> flight;
        user.addToItinerary(flight);
    }

    return is;
}
#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <iostream>

class Flight {
public:
    // Konstruktorok
    Flight();
    Flight(const std::string &departure, const std::string &destination, double price, double popularity = 0.0);
    Flight(const Flight &other);
    Flight(Flight &&other);

    // Értékadás operátorok
    Flight& operator=(const Flight &other);
    Flight& operator=(Flight &&other);

    // Getterek
    std::string getDeparture() const;
    std::string getDestination() const;
    double getPrice() const;
    double getPopularity() const;

    // Egyenlőség operátor
    bool operator==(const Flight &other) const;

    // << operátor
    // Irassuk ki szép formátumban a repülés adatait
    friend std::ostream& operator<<(std::ostream &os, const Flight &flight);
    
    // >> operátor
    // Olvassuk be a repülés adatait
    // A departure, destination, price, popularity sorban szerepelnek
    // A departure és destination nem tartalmaz szóközt
    friend std::istream& operator>>(std::istream &is, Flight &flight);

private:
    std::string departure;
    std::string destination;
    double price;
    double popularity;
};

#endif
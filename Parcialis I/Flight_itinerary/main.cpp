#include <iostream>
#include "flight.h"
#include "user.h"

void testFlightClass() {
   std::cout << std::endl;
   std::cout << "==================== Flight Teszt ====================";
   std::cout << std::endl;

   // Alapértelmezett konstruktor
   Flight flight1;
   std::cout << "Alapértelmezett konstruktor:\n" << flight1 << std::endl;

   // Paraméteres konstruktor
   Flight flight2("New York", "Paris", 500.0, 10.0);
   std::cout << "Paraméteres konstruktor:\n" << flight2 << std::endl;

   // Copy konstruktor
   Flight flight3(flight2);
   std::cout << "Copy konstruktor: " << flight3 << std::endl;

   // Move konstruktor
   Flight flight4(std::move(flight2));
   std::cout << "Move konstruktor:\n" << flight4 << std::endl;

   // Értékadó operátor
   flight1 = flight3;
   std::cout << "Értékadó operátor:\n" << flight1 << std::endl;

   // Move értékadó operátor
   Flight flight5;
   flight5 = std::move(flight3);
   std::cout << "Move értékadó operátor:\n" << flight5 << std::endl;

   // Lekérdezők
   std::cout << "Indulás: " << flight4.getDeparture() << std::endl;
   std::cout << "Érkezés: " << flight4.getDestination() << std::endl;
   std::cout << "Ár: " << flight4.getPrice() << std::endl;
   std::cout << "Népszerűség: " << flight4.getPopularity() << std::endl;

   // Egyenlőség operátor
   if (flight4 == flight5) {
       std::cout << "A repülőjáratok egyenlőek." << std::endl;
   } else {
       std::cout << "A repülőjáratok nem egyenlőek." << std::endl;
   }
}

void testUserClass() {
   std::cout << std::endl;
   std::cout << "==================== User Teszt ====================";
   std::cout << std::endl;

   // Alapértelmezett konstruktor
   User user1;
   std::cout << "Alapértelmezett konstruktor:\n" << user1 << std::endl;

   // Paraméteres konstruktor
   User user2("Alice");
   std::cout << "Paraméteres konstruktor:\n" << user2 << std::endl;

   // Járatok hozzáadása az útitervhez
   Flight flight1("London", "Tokyo", 700.0, 5.0);
   Flight flight2("Tokyo", "Sydney", 400.0, 3.0);

   user2.addToItinerary(flight1);
   user2.addToItinerary(flight2);
   std::cout << "Felhasználó járatokkal:\n" << user2 << std::endl;

   // Duplikált járat hozzáadásának hibakezelése
   try {
       user2.addToItinerary(flight1);
   } catch (const std::invalid_argument &e) {
       std::cout << "Várt kivétel elkapva: " << e.what() << std::endl;
   }

   // Járat eltávolítása az útitervből
   user2.removeFromItinerary("London", "Tokyo");
   std::cout << "Járat eltávolítása után:\n" << user2 << std::endl;

   // Nem létező járat eltávolításának hibakezelése
   try {
       user2.removeFromItinerary("NonExistent", "Destination");
   } catch (const std::invalid_argument &e) {
       std::cout << "Várt kivétel elkapva: " << e.what() << std::endl;
   }

   // Rendezés népszerűség alapján
   user2.sortItineraryByPopularity();
   std::cout << "Rendezett útiterv:\n" << user2 << std::endl;

   // Népszerűtlen járatok eltávolítása
   user2.removeUnpopularFlights(4.0);
   std::cout << "Népszerűtlen járatok eltávolítása után:\n" << user2 << std::endl;

   // Copy konstruktor
   User user3(user2);
   std::cout << "Copy konstruktor:\n" << user3 << std::endl;

   // Move konstruktor
   User user4(std::move(user2));
   std::cout << "Move konstruktor:\n" << user4 << std::endl;

   // Értékadó operátor
   user1 = user3;
   std::cout << "Értékadó operátor:\n" << user1 << std::endl;

   // Move értékadó operátor
   User user5;
   user5 = std::move(user3);
   std::cout << "Move értékadó operátor:\n" << user5 << std::endl;
}

void testInputUser() {
   std::cout << std::endl;
   std::cout << "=================== Felhasználó Bemenet Teszt ===================";
   std::cout << std::endl;

   User user;
   std::cin >> user;
   std::cout << "Felhasználó bemenettel:\n" << user << std::endl;
}

void testInputFlight() {
   std::cout << std::endl;
   std::cout << "=================== Repülőjárat Bemenet Teszt ===================";
   std::cout << std::endl;

   Flight flight;
   std::cin >> flight;
   std::cout << "Repülőjárat bemenettel:\n" << flight << std::endl;
}

int main() {
   testFlightClass();
   testUserClass();
   testInputUser();
   return 0;
}

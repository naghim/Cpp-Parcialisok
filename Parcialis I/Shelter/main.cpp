#include <iostream>
#include <stdexcept>
#include "Dog.h"
#include "Shelter.h"

int main()
{
	Shelter shelter;
	// Uj kutyak letrehozasa
	Dog d1("Claus", "Bulldog", 3);
	Dog d2("Bejgli", "Beagle", 4);
	Dog d3("Rex", "Nemet juhasz", 2);
	// Hozzaadas
	std::cout << "Kutyak hozzaadasa a menhelyhez...\n";
	shelter + d1;
	shelter + d2;
	shelter + d3;
	std::cout << shelter << "\n";
	// Duplikalt hozzaadas - kivetelt kell dobjon
	std::cout << "Duplikált kutya hozzaadasa...\n";
	try
	{
		shelter + d2;
	}
	catch (const std::exception &ex)
	{
		std::cout << "Kivetel elkapva: " << ex.what() << "\n";
	}
	// Indexeles
	std::cout << "Elso kutya indexelessel: " << shelter[0] << "\n";
	// Torles ID alapjan
	std::cout << "Kutya torlése (ID=1)...\n";
	shelter - 1;
	std::cout << shelter << "\n";
	// Veletlenszeru orokbeadas
	std::cout << "Veletlenszeru orokbeadas...\n";
	Dog adopted;
	adopted = shelter.adoptRandom();
	std::cout << "Orokbe adott kutya: " << adopted << "\n";
	std::cout << "\nMenhely aktualis allapota:\n"
			  << shelter << "\n";
	// Hibas indexeles
	std::cout << "Hibas indexeles kiprobalasa...\n";
	try
	{
		std::cout << shelter[10] << "\n";
	}
	catch (const std::out_of_range &ex)
	{
		std::cout << "Kivetel elkapva: " << ex.what() << "\n";
	}
	return 0;
}

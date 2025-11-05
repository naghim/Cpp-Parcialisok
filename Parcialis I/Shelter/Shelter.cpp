#include "Shelter.h"
#include <algorithm>
#include <random>
#include <stdexcept>
#include <ctime>

void Shelter::addDog(const Dog &dog)
{
	for (const auto &d : dogs)
	{
		// két kutya egyenlő, ha azonos az ID-jük
		// ezt csinálja a ==operátor a Dog osztályban
		if (d == dog)
		{
			throw std::invalid_argument("Ilyen ID-ju kutya mar letezik");
		}
	}
	dogs.push_back(dog);
}

void Shelter::removeDog(int id)
{
	auto it = std::find_if(dogs.begin(), dogs.end(), [id](const Dog &d)
						   { return d.getId() == id; });
	if (it != dogs.end())
	{
		dogs.erase(it);
	}
	else
	{
		throw std::invalid_argument("Ilyen ID-ju kutya nem találhato");
	}

	/*
	 * egy másik megoldás:
	 *
	 * for (auto it = dogs.begin(); it != dogs.end(); ++it)
	 * {
	 *     if (it->getId() == id)
	 *     {
	 *         dogs.erase(it);
	 *         return;
	 *     }
	 * }
	 * throw std::invalid_argument("Ilyen ID-ju kutya nem találhato");
	 */

	/*
	 * favágó módszer, ha más nem jut eszünkbe:
	 *
	 * vector<Dog> newDogs;
	 * for (const auto &d : dogs)
	 * {
	 * 	if (d.getId() != id)
	 * 	{
	 * 		newDogs.push_back(d);
	 * 	}
	 * }
	 *
	 * if (newDogs.size() == dogs.size())
	 * {
	 * 	throw std::invalid_argument("Ilyen ID-ju kutya nem találhato");
	 * }
	 *
	 * dogs = std::move(newDogs);
	 */
}

Dog Shelter::adoptRandom()
{
	if (dogs.empty())
	{
		throw std::out_of_range("Nincs orokbeadhato kutya");
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, dogs.size() - 1);
	int index = dist(gen);

	Dog adopted = dogs[index];
	// Kutyát randomizáltunk, nem indexet,
	// ezért hogy eltávolítsuk, az ID-ját használjuk
	removeDog(adopted.getId());

	return adopted;
}

const Dog &Shelter::operator[](int index) const
{
	if (index >= dogs.size() || index < 0)
	{
		throw std::out_of_range("Indexhiba");
	}
	return dogs[index];
}

std::ostream &operator<<(std::ostream &os, const Shelter &shelter)
{
	if (shelter.dogs.empty())
	{
		os << "A menhely ures.";
	}
	else
	{
		os << "A menhelyen levo kutyak:\n";
		for (const auto &dog : shelter.dogs)
		{
			os << dog << "\n";
		}
	}
	return os;
}

Shelter &operator+(Shelter &shelter, const Dog &dog)
{
	shelter.addDog(dog);
	return shelter;
}

Shelter &operator-(Shelter &shelter, int id)
{
	shelter.removeDog(id);
	return shelter;
}

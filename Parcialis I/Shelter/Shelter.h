#ifndef SHELTER_H
#define SHELTER_H

#include <vector>
#include <iostream>
#include "Dog.h"

class Shelter
{
private:
	std::vector<Dog> dogs;

public:
	void addDog(const Dog &dog);
	void removeDog(int id);
	Dog adoptRandom();

	const Dog &operator[](int index) const;

	friend std::ostream &operator<<(std::ostream &os, const Shelter &shelter);
	friend Shelter &operator+(Shelter &shelter, const Dog &dog);
	friend Shelter &operator-(Shelter &shelter, int id);
};

#endif // SHELTER_H

#include "Dog.h"

int Dog::ID_COUNTER = 1;

Dog::Dog()
{
	id = ID_COUNTER++;
	name = "";
	breed = "";
	age = 0;
}

Dog::Dog(const std::string &name, const std::string &breed, int age)
{
	id = ID_COUNTER++;
	this->name = name;
	this->breed = breed;
	this->age = age;
}

int Dog::getId() const
{
	return id;
}

bool Dog::operator==(const Dog &other) const
{
	return id == other.id;
}

std::ostream &operator<<(std::ostream &os, const Dog &dog)
{
	os << "ID: " << dog.id << ", Nev: " << dog.name << ", Fajta: " << dog.breed << ", Kor: " << dog.age;
	return os;
}

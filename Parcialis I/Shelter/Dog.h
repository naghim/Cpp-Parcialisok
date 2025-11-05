#ifndef DOG_H
#define DOG_H

#include <string>
#include <iostream>

class Dog
{
private:
	static int ID_COUNTER;
	int id;
	std::string name;
	std::string breed;
	int age;

public:
	Dog();
	Dog(const std::string &name, const std::string &breed, int age);
	int getId() const;
	bool operator==(const Dog &other) const;
	friend std::ostream &operator<<(std::ostream &os, const Dog &dog);
};

#endif // DOG_H

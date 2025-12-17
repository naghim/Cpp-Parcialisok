#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>
#include <iostream>

class Zombie
{
protected:
	// örökölhető közös adatok
	std::string ipAddress;
	std::string country;
	int cpuUsagePercentage;

public:
	Zombie(std::string ip, std::string country, int cpuUsage);
	virtual ~Zombie() {};

	std::string getIpAddress() const;
	std::string getCountry() const;
	int getCpuUsagePercentage() const;
	void setCpuUsage(int);
	bool isOnline() const;

	// egyszerűsített típus lekérdezés, helyette lehetne Dynamic Cast-tal is megoldani
	virtual std::string getType() const = 0;
	virtual void prettyPrint(std::ostream &) const = 0;
	friend std::ostream &operator<<(std::ostream &, const Zombie &);
};

#endif
#include "zombie.h"

Zombie::Zombie(std::string ip, std::string country, int cpuUsage)
	: ipAddress(ip), country(country), cpuUsagePercentage(cpuUsage) {};

std::string Zombie::getIpAddress() const
{
	return ipAddress;
}

std::string Zombie::getCountry() const
{
	return country;
}

int Zombie::getCpuUsagePercentage() const
{
	return cpuUsagePercentage;
}

bool Zombie::isOnline() const
{
	return cpuUsagePercentage <= 90;
}

void Zombie::setCpuUsage(int cpu)
{
	if (cpu > 100)
		cpuUsagePercentage = 100;
	else if (cpu < 0)
		cpuUsagePercentage = 0;
	else
		cpuUsagePercentage = cpu;
}

std::ostream &operator<<(std::ostream &os, const Zombie &z)
{
	z.prettyPrint(os);
	return os;
}

#ifndef LINUXZOMBIE_H
#define LINUXZOMBIE_H

#include "zombie.h"
#include <string>
#include <sstream>

class LinuxZombie : public Zombie
{
private:
	bool root;

public:
	LinuxZombie(std::string ip, std::string country, int cpu_usage, bool root)
		: Zombie(ip, country, cpu_usage), root(root) {};
	~LinuxZombie() override {};

	bool isRoot() const { return root; }
	std::string getType() const override { return "linux"; }

	void prettyPrint(std::ostream &os) const override
	{
		os << "[Linux] IP: " << getIpAddress() << ", from " << getCountry() << std::endl
		   << "\tCPU: " << getCpuUsagePercentage() << "%, Root: " << (root ? "true" : "false")
		   << ", Status: " << (isOnline() ? "Online" : "Offline");
	}
};

#endif
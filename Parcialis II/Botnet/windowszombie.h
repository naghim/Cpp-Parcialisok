#ifndef WINDOWSZOMBIE_H
#define WINDOWSZOMBIE_H

#include "zombie.h"
#include <string>
#include <sstream>

class WindowsZombie : public Zombie
{
private:
	std::string windowsVersion;

public:
	WindowsZombie(std::string ip, std::string country, int cpu_usage, std::string version)
		: Zombie(ip, country, cpu_usage), windowsVersion(version) {};
	~WindowsZombie() override {};

	std::string getWindowsVersion() const { return windowsVersion; }
	std::string getType() const override { return "windows"; }

	void prettyPrint(std::ostream &os) const override
	{
		os << "[Windows] IP: " << getIpAddress() << ", from " << getCountry() << std::endl
		   << "\tCPU: " << getCpuUsagePercentage() << "%, Version: " << windowsVersion
		   << ", Status: " << (isOnline() ? "Online" : "Offline");
	}
};

#endif
#include "c2server.h"
#include "windowszombie.h"
#include "linuxzombie.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

C2Server::C2Server()
{
	std::ifstream file("zombies.txt");
	if (!file.is_open())
	{
		std::cerr << "Error: Could not open zombies.txt" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		std::istringstream iss(line);
		std::string ip, country, type, extra;
		int cpu;

		iss >> ip >> country >> cpu >> type >> extra;

		if (type == "Windows")
		{
			zombies.push_back(new WindowsZombie(ip, country, cpu, extra));
		}
		else if (type == "Linux")
		{
			bool root = (extra == "true");
			zombies.push_back(new LinuxZombie(ip, country, cpu, root));
		}
	}
	file.close();
	std::cout << "Loaded " << zombies.size() << " zombie(s) from zombies.txt" << std::endl;
}

C2Server::~C2Server()
{
	for (auto z : zombies)
	{
		delete z;
	}
	zombies.clear();
}

void C2Server::printStatus() const
{
	std::cout << "\n=== ALL ZOMBIES STATUS ===" << std::endl;
	for (const auto &z : zombies)
	{
		std::cout << *z << std::endl;
	}
	std::cout << "Total: " << zombies.size() << " zombie(s)\n\n";
}

void C2Server::printByStatus(std::string status) const
{
	std::cout << "\n=== " << status << " ZOMBIES ===" << std::endl;
	int count = 0;
	for (const auto &z : zombies)
	{
		// ha a státus ONLINE és zombi is online, vagy OFFLINE és zombi is offline
		bool show = (status == "ONLINE" && z->isOnline()) ||
					(status == "OFFLINE" && !z->isOnline());
		if (show)
		{
			std::cout << *z << std::endl;
			count++;
		}
	}
	std::cout << "Total " << status << ": " << count << " zombie(s)\n\n";
}

void C2Server::setCpuUsage(const std::string &ip, int cpu_usage)
{
	for (auto &z : zombies)
	{
		if (z->getIpAddress() == ip)
		{
			z->setCpuUsage(cpu_usage);
			std::cout << "Updated CPU usage for " << ip << " to " << cpu_usage << "%" << std::endl;
			return;
		}
	}
	throw std::runtime_error("Zombie with IP " + ip + " not found");
}

std::vector<Zombie *> C2Server::getByType(const std::string &type) const
{
	std::vector<Zombie *> result;
	for (const auto &z : zombies)
	{
		// egyszerű típus ellenőrzés
		// helyette lehetne Dynamic Cast-tal is megoldani
		/*if ((type == "linux" && dynamic_cast<LinuxZombie *>(z)) ||
		 * 	 (type == "windows" && dynamic_cast<WindowsZombie *>(z)))
		 * {
		 * 	 result.push_back(z);
		 * }
		 */

		if (z->getType() == type)
		{
			result.push_back(z);
		}
	}

	std::cout << "\n=== " << type << " ZOMBIES ===" << std::endl;
	for (const auto &z : result)
	{
		std::cout << *z << std::endl;
	}
	std::cout << "Total " << type << ": " << result.size() << " zombie(s)\n\n";

	return result;
}

void C2Server::simulateDDoS(const std::string &target_ip) const
{
	std::cout << "\n=== INITIATING DDoS ATTACK on " << target_ip << " ===" << std::endl;
	int participants = 0;

	for (auto &z : zombies)
	{
		if (z->isOnline())
		{
			int newCpu = z->getCpuUsagePercentage() + 45;
			z->setCpuUsage(newCpu);
			participants++;
			std::cout << "Zombie " << z->getIpAddress() << " attacking - CPU now at "
					  << z->getCpuUsagePercentage() << "% - "
					  << (z->isOnline() ? "still online" : "went offline") << std::endl;
		}
	}

	std::cout << "DDoS attack completed with " << participants << " participating zombie(s)\n\n";
}

void C2Server::deleteOfflineZombies()
{
	std::cout << "\n=== DELETING OFFLINE ZOMBIES ===" << std::endl;
	int deleted = 0;

	auto it = zombies.begin();
	while (it != zombies.end())
	{
		if (!(*it)->isOnline())
		{
			std::cout << "Deleting: " << **it << std::endl;
			delete *it;
			it = zombies.erase(it);
			deleted++;
		}
		else
		{
			++it;
		}
	}

	std::cout << "Deleted " << deleted << " offline zombie(s). Remaining: " << zombies.size() << "\n\n";
}

void C2Server::processCommands(const std::string &filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Error: Could not open " << filename << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		std::istringstream iss(line);
		std::string command, param;
		iss >> command >> param;

		std::cout << "\n>>> Executing command: " << line << std::endl;

		if (command == "PRINT_STATUS")
		{
			printStatus();
		}
		else if (command == "PRINT_ONLINE")
		{
			printByStatus("ONLINE");
		}
		else if (command == "PRINT_OFFLINE")
		{
			printByStatus("OFFLINE");
		}
		else if (command == "SET_CPU")
		{
			std::string ip = param;
			int cpu;
			iss >> cpu;
			try
			{
				setCpuUsage(ip, cpu);
			}
			catch (const std::runtime_error &e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
		else if (command == "GET_LINUX")
		{
			getByType("linux");
		}
		else if (command == "GET_WINDOWS")
		{
			getByType("windows");
		}
		else if (command == "DDOS")
		{
			simulateDDoS(param);
		}
		else if (command == "DELETE_OFFLINE")
		{
			deleteOfflineZombies();
		}
		else
		{
			std::cout << "Unknown command: " << command << std::endl;
		}
	}
	file.close();
}

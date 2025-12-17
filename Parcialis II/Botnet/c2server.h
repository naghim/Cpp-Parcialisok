#ifndef C2SERVER_H
#define C2SERVER_H

#include "zombie.h"
#include <vector>
#include <string>

class C2Server
{
private:
	// Zombie*, mert különböző (al)típusú zombik lehetnek → így lesz polimorfikus a tárolás
	std::vector<Zombie *> zombies;

public:
	C2Server();
	// Zombie*-okat tárolunk, ezért meg kell írjuk a destruktort is
	~C2Server();
	void processCommands(const std::string &filename);

	// PRINT_STATUS – az összes zombi adatait kiírja
	void printStatus() const;

	// PRINT_ONLINE - kiírja az online zombik adatait
	// PRINT_OFFLINE - kiírja az offline zombik adatait
	void printByStatus(std::string) const;

	// SET_CPU <IP> – módosítja a CPU terhelést az adott IP című gépnek
	void setCpuUsage(const std::string &ip, int cpu_usage);

	// GET_LINUX – csak a Linux alapú zombikat listáját téríti vissza
	// GET_WINDOWS – csak a Windows OS-es zombik listáját téríti vissza
	std::vector<Zombie *> getByType(const std::string &type) const;
	// DDOS <IP> – szimulált támadást indít a megadott IP cím ellen csak az online zombik segítésével:
	// •– ha a CPU terheltség > 90% → túlterhelődött → offline, máskülönben online-nak számít
	void simulateDDoS(const std::string &target_ip) const;

	// DELETE_OFFLINE - törli az offline zombikat
	void deleteOfflineZombies();
};

#endif
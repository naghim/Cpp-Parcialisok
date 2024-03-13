#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include "EvesKiadas.h"

EvesKiadas::EvesKiadas(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Nem sikerült megnyitni a fájlt: " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string honap, kiadas;
        int osszeg;
        ss >> honap >> kiadas >> osszeg;
        ujKiadas(honap, kiadas, osszeg);
    }

    // RAII miatt nem szükségeltetik a file.close();
    // file.close();
}

void EvesKiadas::ujKiadas(const std::string &honap, const std::string &kiadas, int osszeg)
{
    kiadasok[honap].push_back(make_pair(kiadas, osszeg));
}

void EvesKiadas::listazas() const
{
    for (const auto &entry : kiadasok)
    {
        std::cout << entry.first << ":" << std::endl;
        for (const auto &pair : entry.second)
        {
            std::cout << "\t - " << pair.first << ": " << pair.second << std::endl;
        }
        std::cout << std::endl;
    }
}

std::set<std::string> EvesKiadas::kiadasiKategoriak() const
{
    std::set<std::string> kategoriak;
    for (const auto &entry : kiadasok)
    {
        for (const auto &pair : entry.second)
        {
            kategoriak.insert(pair.first);
        }
    }
    return kategoriak;
}

double EvesKiadas::honaponkentiAtlagKiadas(const std::string &honap) const
{
    if (honap.empty())
    {
        double osszeg = 0;
        int darab = 0;
        for (const auto &entry : kiadasok)
        {
            for (const auto &pair : entry.second)
            {
                osszeg += pair.second;
                darab++;
            }
        }
        return osszeg / darab;
    }

    if (kiadasok.find(honap) != kiadasok.end())
    {
        double osszeg = 0;
        int darab = 0;
        for (const auto &pair : kiadasok.at(honap))
        {
            osszeg += pair.second;
            darab++;
        }
        return osszeg / darab;
    }

    std::cout << "Nincs adat a megadott hónaphoz: " << honap << std::endl;
    return 0;
}

double EvesKiadas::kategoriankentiAtlagKiadas(const std::string &kategoria) const
{
    if (kiadasok.empty())
    {
        std::cout << "Nem került kategória megadásra." << std::endl;
        return 0.0;
    }

    double osszeg = 0.0;
    int darab = 0;

    for (const auto &entry : kiadasok)
    {
        for (const auto &pair : entry.second)
        {
            if (pair.first == kategoria)
            {
                osszeg += pair.second;
                darab++;
            }
        }
    }

    if (darab == 0)
    {
        std::cout << "Nincs adat a megadott kategóriához: " << kategoria << std::endl;
        return 0.0;
    }

    return osszeg / darab;
}

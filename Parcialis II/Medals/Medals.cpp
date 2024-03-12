#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include "Medals.h"

Eremtablazat::Eremtablazat(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Hiba: A fajl nem nyithato meg!" << std::endl;
        return;
    }
    std::string nev, medal;
    while (file >> nev >> medal)
    {
        ujMedal(nev, medal);
    }
    // a fájt automatikusan bezáródik, amikor az ifstream destruktora meghívódik
    // file.close();
}

void Eremtablazat::listazas() const
{
    for (const auto &entry : medalok)
    {
        std::cout << entry.first << ":" << std::endl;
        for (const auto &medal : entry.second)
        {
            std::cout << "- " << medal.first << ": " << medal.second << std::endl;
        }
        std::cout << std::endl;
    }
}

void Eremtablazat::ujMedal(const std::string &nev, const std::string &medalTipus)
{
    if (medalok.find(nev) == medalok.end())
    {
        // ha nincs benne a sportoló, akkor hozzáadjuk
        medalok[nev] = {{medalTipus, 1}};
        return;
    }

    for (auto &medal : medalok[nev])
    {
        if (medal.first == medalTipus)
        {
            // ha már van ilyen típusú érméje a sportolónak, akkor növeljük a darabszámát
            medal.second++;
            return;
        }
    }

    // ha nem volt ilyen típusú érméje a sportolónak, akkor hozzáadjuk
    medalok[nev].push_back({medalTipus, 1});
}

std::set<std::string> Eremtablazat::sportolok() const
{
    std::set<std::string> sportolok_nevei;
    for (const auto &entry : medalok)
    {
        sportolok_nevei.insert(entry.first);
    }
    return sportolok_nevei;
}

int Eremtablazat::medalokSzama(const std::string &medalTipus) const
{
    int sum = 0;
    for (const auto &entry : medalok)
    {
        for (const auto &medal : entry.second)
        {
            if (medalTipus.empty() || medal.first == medalTipus)
            {
                sum += medal.second;
            }
        }
    }
    return sum;
}

std::string Eremtablazat::legtobbMedal()
{
    std::string legtobb = "";
    int max_medal = 0;
    for (const auto &entry : medalok)
    {
        int sum = 0;
        for (const auto &medal : entry.second)
        {
            sum += medal.second;
        }
        if (sum > max_medal)
        {
            max_medal = sum;
            legtobb = entry.first;
        }
    }
    return legtobb;
}

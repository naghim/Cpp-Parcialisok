#include <iostream>
#include <fstream>
#include "Medals.h"

int main()
{
    Eremtablazat eremtablazat("medals.txt");
    eremtablazat.listazas();
    std::cout << "Sportolok szama: " << eremtablazat.sportolok().size() << std::endl;
    std::cout << "Osszesen " << eremtablazat.medalokSzama("") << " medal van az eremtablazatban." << std::endl;
    std::cout << "Osszesen " << eremtablazat.medalokSzama("arany") << " arany medal van az eremtablazatban." << std::endl;
    std::cout << "Legtobb medalt nyert sportolo: " << eremtablazat.legtobbMedal() << std::endl;
    return 0;
}

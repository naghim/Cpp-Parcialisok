#include <iostream>
#include <set>
#include "EvesKiadas.h"

int main()
{
    EvesKiadas ev("expenses.txt");

    std::cout << "Kiadasok listazasa:" << std::endl;
    ev.listazas();

    std::cout << "Kiadasi kategoriak:" << std::endl;
    std::set<std::string> kategoriak = ev.kiadasiKategoriak();
    for (const auto &kategori : kategoriak)
    {
        std::cout << kategori << std::endl;
    }

    std::cout << "Atlagos kiadas januarban: " << ev.honaponkentiAtlagKiadas("januar") << std::endl;
    std::cout << "Atlagos kiadas az osszes honapban: " << ev.honaponkentiAtlagKiadas("") << std::endl;

    std::cout << "Atlagos lakber kategoriankenti kiadas: " << ev.kategoriankentiAtlagKiadas("kozlekedes") << std::endl;

    return 0;
}
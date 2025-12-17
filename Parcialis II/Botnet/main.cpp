#include "c2server.h"
#include <iostream>

int main()
{
    C2Server server;

    // Parancsok feldolgozása
    server.processCommands("commands.txt");

    return 0;
}

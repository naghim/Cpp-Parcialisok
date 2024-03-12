#include <iostream>

#include "LinkShortenerService.h"

int main()
{
    LinkShortenerService linkShortener;

    try
    {
        linkShortener.processInputFile("linkrovidites.txt");

        std::string apiKey = "bb702ffd-640d-40fe-8520-94bac77c30aa";
        std::string shortLink = linkShortener.shortenLink("https://www.youtube.com/watch?v=8Wh8FaZmAVQ", apiKey);
        std::cout << "Shortened link: " << shortLink << std::endl;

        std::string longLink = linkShortener.resolveLink(shortLink, apiKey);
        std::cout << "Resolved link: " << longLink << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
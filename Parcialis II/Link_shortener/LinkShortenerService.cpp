#include <unordered_map>
#include <random>
#include <string>
#include <fstream>
#include <iostream>

#include "LinkShortenerService.h"

std::string LinkShortenerService::shortenLink(const std::string &longLink, const std::string &apiKey)
{
    std::string shortLink = generateRandomLink();

    shortenedLinks[shortLink] = ShortenedLink(longLink);
    shortenedLinks[shortLink].addApiKey(apiKey);
    return shortLink;
}

std::string LinkShortenerService::resolveLink(const std::string &shortLink, const std::string &apiKey)
{
    if (shortenedLinks.find(shortLink) == shortenedLinks.end())
    {
        throw std::invalid_argument("Shortened link not found");
    }

    if (!shortenedLinks[shortLink].hasAccess(apiKey))
    {
        throw std::invalid_argument("Unauthorized access");
    }

    shortenedLinks[shortLink].useLink();
    return shortenedLinks[shortLink].getLongLink();
}

void LinkShortenerService::addApiKey(const std::string &shortLinkId, const std::string &apiKey)
{
    if (shortenedLinks.find(shortLinkId) == shortenedLinks.end())
    {
        throw std::invalid_argument("Shortened link not found");
    }

    shortenedLinks[shortLinkId].addApiKey(apiKey);
}

void LinkShortenerService::processInputFile(const std::string &filename)
{
    std::ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        throw std::invalid_argument("File not found");
    }

    std::string longLink;
    std::string apiKey;
    int apiKeyCount;

    while (!inputFile.eof())
    {
        inputFile >> longLink >> apiKeyCount;
        std::string shortLink = generateRandomLink();

        shortenedLinks[shortLink] = ShortenedLink(longLink);

        for (int i = 0; i < apiKeyCount; ++i)
        {
            inputFile >> apiKey;
            shortenedLinks[shortLink].addApiKey(apiKey);
        }
    }
}

std::string generateRandomLink()
{
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> numbers(0, (int)charset.size() - 1);
    std::string randomString(7, 0);

    for (int i = 0; i < 7; ++i)
    {
        randomString.push_back(charset[numbers(rng)]);
    }

    return randomString;
}
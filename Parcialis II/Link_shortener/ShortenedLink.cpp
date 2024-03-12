#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "ShortenedLink.h"

ShortenedLink::ShortenedLink() : longLink(""), usedTimes(0) {}

ShortenedLink::ShortenedLink(const std::string &longLink) : longLink(longLink), usedTimes(0) {}

std::string ShortenedLink::getLongLink() const
{
    return longLink;
}

std::vector<std::string> ShortenedLink::getApiKeys() const
{
    return apiKeys;
}

bool ShortenedLink::hasAccess(std::string apiKey) const
{
    return std::find(apiKeys.begin(), apiKeys.end(), apiKey) != apiKeys.end();
}

void ShortenedLink::addApiKey(std::string apiKey)
{
    if (hasAccess(apiKey))
    {
        throw std::invalid_argument("API key has already been added");
    }

    apiKeys.push_back(apiKey);
}

void ShortenedLink::useLink()
{
    usedTimes++;
}
#include <unordered_map>
#include <string>

#include "ShortenedLink.h"
#include "ILinkShortenerService.h"

class LinkShortenerService : public ILinkShortenerService
{
public:
    std::string shortenLink(const std::string &longLink, const std::string &apiKey);
    std::string resolveLink(const std::string &shortLink, const std::string &apiKey);
    void addApiKey(const std::string &shortLinkId, const std::string &apiKey);
    void processInputFile(const std::string &filename);

private:
    std::unordered_map<std::string, ShortenedLink> shortenedLinks;
};

std::string generateRandomLink();
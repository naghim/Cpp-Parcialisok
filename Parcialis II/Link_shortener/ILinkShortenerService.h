#include <string>

class ILinkShortenerService
{
public:
    virtual std::string shortenLink(const std::string &longLink, const std::string &apiKey) = 0;
    virtual std::string resolveLink(const std::string &shortLink, const std::string &apiKey) = 0;
    virtual void addApiKey(const std::string &shortLink, const std::string &apiKey) = 0;
    virtual void processInputFile(const std::string &filename) = 0;
};

std::string generateRandomLink();
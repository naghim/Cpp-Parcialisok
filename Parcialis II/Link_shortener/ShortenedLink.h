#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class ShortenedLink
{
public:
    ShortenedLink();
    ShortenedLink(const std::string &longLink);

    std::string getLongLink() const;
    std::vector<std::string> getApiKeys() const;
    bool hasAccess(std::string apiKey) const;
    void addApiKey(std::string apiKey);
    void useLink();

private:
    std::string longLink;
    std::vector<std::string> apiKeys;
    int usedTimes;
};
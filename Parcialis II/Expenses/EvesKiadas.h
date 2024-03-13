#include <map>
#include <vector>
#include <set>
#include <string>

class EvesKiadas
{
private:
    std::map<std::string, std::vector<std::pair<std::string, int>>> kiadasok;

public:
    EvesKiadas(const std::string &filename);
    void ujKiadas(const std::string &honap, const std::string &kiadas, int osszeg);
    void listazas() const;
    std::set<std::string> kiadasiKategoriak() const;
    double honaponkentiAtlagKiadas(const std::string &honap) const;
    double kategoriankentiAtlagKiadas(const std::string &kategoria) const;
};

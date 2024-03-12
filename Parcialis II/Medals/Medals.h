#include <map>
#include <vector>
#include <set>
#include <string>

class Eremtablazat
{
private:
    std::map<std::string, std::vector<std::pair<std::string, int>>> medalok;

public:
    Eremtablazat(const std::string &filename);
    void listazas() const;
    void ujMedal(const std::string &nev, const std::string &medalTipus);
    std::set<std::string> sportolok() const;
    int medalokSzama(const std::string &medalTipus) const;
    std::string legtobbMedal();
};
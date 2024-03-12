#include <iostream>
#include <string>
#include <stdexcept>

class CouponCode
{
private:
    std::string codeName;
    std::string description;
    int usesRemaining;

public:
    CouponCode(std::string name, std::string desc, int uses);
    std::string getCodeName() const;
    bool isUsable() const;
    std::string useCoupon();
};

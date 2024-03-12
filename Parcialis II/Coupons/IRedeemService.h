#include <string>

class IRedeemService
{
public:
    virtual std::string redeemCoupon(const std::string &code) = 0;
    virtual std::string generateCoupon(const std::string &description) = 0;
    virtual int countUsableCoupons() const = 0;
    virtual void readCouponsFromFile(const std::string &filename) = 0;
};
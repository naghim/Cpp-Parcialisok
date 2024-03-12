#include <vector>
#include <string>

#include "CouponCode.h"
#include "IRedeemService.h"

class RedeemService : public IRedeemService
{
public:
    std::string redeemCoupon(const std::string &code) override;
    std::string generateCoupon(const std::string &description) override;
    int countUsableCoupons() const override;
    void readCouponsFromFile(const std::string &filename) override;

private:
    std::vector<CouponCode> couponCodes;
};

std::string generateCouponName();
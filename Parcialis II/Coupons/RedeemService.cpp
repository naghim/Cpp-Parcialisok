#include <fstream>
#include <random>
#include <algorithm>

#include "RedeemService.h"

std::string RedeemService::redeemCoupon(const std::string &code)
{
    auto it = std::find_if(couponCodes.begin(), couponCodes.end(), [&](const CouponCode &coupon)
                           { return coupon.getCodeName() == code; });

    if (it != couponCodes.end())
    {
        return it->useCoupon();
    }

    throw std::invalid_argument("Coupon code not found.");
}

std::string RedeemService::generateCoupon(const std::string &description)
{
    std::string name = generateCouponName();
    couponCodes.emplace_back(name, description, 1);
    return name;
}

int RedeemService::countUsableCoupons() const
{
    return (int)std::count_if(couponCodes.begin(), couponCodes.end(), [](const CouponCode &coupon)
                              { return coupon.isUsable(); });
}

void RedeemService::readCouponsFromFile(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::invalid_argument("File not found.");
    }

    std::string name, description;
    int uses;

    while (file >> name >> uses)
    {
        std::getline(file >> std::ws, description);
        couponCodes.emplace_back(name, description, uses);
    }
}

std::string generateCouponName()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(0, 25);

    std::string name = "";

    for (int i = 0; i < 10; ++i)
    {
        int randomValue = dist(rng);
        name += static_cast<char>('A' + randomValue);
    }

    return name;
}
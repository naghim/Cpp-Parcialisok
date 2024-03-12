#include <iostream>
#include <string>
#include <stdexcept>

#include "CouponCode.h"

CouponCode::CouponCode(std::string name, std::string desc, int uses)
    : codeName(name), description(desc), usesRemaining(uses) {}

std::string CouponCode::getCodeName() const
{
    return codeName;
}

bool CouponCode::isUsable() const
{
    return usesRemaining > 0;
}

std::string CouponCode::useCoupon()
{
    if (usesRemaining > 0)
    {
        usesRemaining--;
        return description;
    }
    else
    {
        throw std::logic_error("Coupon has already been used up.");
    }
}

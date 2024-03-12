#include <iostream>
#include <stdexcept>

#include "RedeemService.h"

int main()
{
    RedeemService service;

    // Tesztelés
    service.readCouponsFromFile("kuponbevaltas.txt");

    std::cout << "Usable coupons before generation: " << service.countUsableCoupons() << std::endl;

    std::string newCoupon = service.generateCoupon("Newly generated coupon");
    std::cout << "Generated coupon code: " << newCoupon << std::endl;

    std::cout << "Usable coupons after generation: " << service.countUsableCoupons() << std::endl;

    try
    {
        std::cout << "Redeemed coupon: " << service.redeemCoupon(newCoupon) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "Random coupon name: " << generateCouponName() << std::endl;

    return 0;
}
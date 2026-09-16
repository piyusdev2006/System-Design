#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

class Coupon {
private:
    std::string code;
    double discountPercent;
    double flatDiscount;

public:
    Coupon(std::string couponCode, double percent, double flatAmount);
    double calculateDiscount(double amount) const;
};

class CouponManager {
public:
    static Coupon* findCoupon(const std::string& code);
};

class PaymentGateway {
public:
    static double applyCouponAndPay(double amount, const std::string& couponCode);
};

#endif

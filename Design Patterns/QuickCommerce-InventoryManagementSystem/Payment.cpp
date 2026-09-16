#include "Payment.h"
#include <algorithm>
#include <iostream>
#include <utility>

Coupon::Coupon(std::string couponCode, double percent, double flatAmount)
    : code(std::move(couponCode)), discountPercent(percent),
      flatDiscount(flatAmount) {}

double Coupon::calculateDiscount(double amount) const {
    double percentageDiscount = amount * discountPercent / 100.0;
    return std::min(amount, std::max(percentageDiscount, flatDiscount));
}

Coupon* CouponManager::findCoupon(const std::string& code) {
    if (code == "SAVE10") {
        return new Coupon(code, 10.0, 0.0);
    }
    if (code == "FLAT50") {
        return new Coupon(code, 0.0, 50.0);
    }
    return nullptr;
}

double PaymentGateway::applyCouponAndPay(
    double amount, const std::string& couponCode) {
    double discount = 0.0;
    if (!couponCode.empty()) {
        Coupon* coupon = CouponManager::findCoupon(couponCode);
        if (coupon == nullptr) {
            std::cout << "[PaymentGateway] Invalid coupon: "
                      << couponCode << "\n";
        } else {
            discount = coupon->calculateDiscount(amount);
            std::cout << "[Coupon] " << couponCode << " applied. Discount: ₹"
                      << discount << "\n";
            delete coupon;
        }
    }

    double finalAmount = amount - discount;
    std::cout << "[PaymentGateway] Payment successful. Paid: ₹"
              << finalAmount << "\n";
    return finalAmount;
}

#ifndef ORDER_H
#define ORDER_H

#include "DarkStore.h"
#include "Payment.h"
#include "RiderMapping.h"
#include "User.h"
#include <vector>

class Order {
public:
    static int nextId;
    int orderId;
    User* user;
    std::vector<std::pair<Product*, int>> items;
    std::vector<DeliveryPartner*> partners;
    double totalAmount;
    double discountAmount;

    explicit Order(User* orderUser);
    ~Order();
};

class OrderManager {
private:
    std::vector<Order*> orders;
    RiderMappingAlgorithm riderMapping;
    static OrderManager* instance;
    OrderManager();

public:
    static OrderManager* getInstance();
    ~OrderManager();
    void placeOrder(User* user, Cart* cart, const std::string& couponCode = "");
    std::vector<Order*> getAllOrders() const;
};

#endif

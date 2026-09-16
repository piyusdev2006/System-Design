#ifndef USER_H
#define USER_H

#include "Product.h"
#include <utility>
#include <vector>
#include <string>

class Cart {
private:
    std::vector<std::pair<Product*, int>> items;

public:
    ~Cart();
    void addItem(int sku, int quantity);
    double getTotal() const;
    std::vector<std::pair<Product*, int>> getItems() const;
};

class User {
public:
    std::string name;
    double x;
    double y;

private:
    Cart* cart;

public:
    User(std::string userName, double xCoordinate, double yCoordinate);
    ~User();
    Cart* getCart() const;
};

class DeliveryPartner {
public:
    std::string name;
    explicit DeliveryPartner(std::string partnerName);
};

#endif

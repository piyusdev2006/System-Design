#include "User.h"
#include <iostream>
#include <utility>

Cart::~Cart() {
    for (auto& item : items) {
        delete item.first;
    }
}

void Cart::addItem(int sku, int quantity) {
    Product* product = ProductFactory::createProduct(sku);
    items.push_back({product, quantity});
    std::cout << "[Cart] Added SKU " << sku << " (" << product->getName()
              << ") x" << quantity << std::endl;
}

double Cart::getTotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.first->getPrice() * item.second;
    }
    return total;
}

std::vector<std::pair<Product*, int>> Cart::getItems() const {
    return items;
}

User::User(std::string userName, double xCoordinate, double yCoordinate)
    : name(std::move(userName)), x(xCoordinate), y(yCoordinate),
      cart(new Cart()) {}

User::~User() { delete cart; }

Cart* User::getCart() const { return cart; }

DeliveryPartner::DeliveryPartner(std::string partnerName)
    : name(std::move(partnerName)) {}

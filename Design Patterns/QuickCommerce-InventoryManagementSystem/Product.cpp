#include "Product.h"
#include <utility>

Product::Product(int id, std::string nm, double pr)
    : sku(id), name(std::move(nm)), price(pr) {}

int Product::getSku() const { return sku; }
std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }

Product* ProductFactory::createProduct(int sku) {
    std::string name;
    double price;

    if (sku == 101) {
        name = "Apple";
        price = 20;
    } else if (sku == 102) {
        name = "Banana";
        price = 10;
    } else if (sku == 103) {
        name = "Chocolate";
        price = 50;
    } else if (sku == 201) {
        name = "T-Shirt";
        price = 500;
    } else if (sku == 202) {
        name = "Jeans";
        price = 1000;
    } else {
        name = "Item" + std::to_string(sku);
        price = 100;
    }

    return new Product(sku, name, price);
}

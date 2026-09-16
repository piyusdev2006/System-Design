#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int sku;
    std::string name;
    double price;

public:
    Product(int id, std::string nm, double pr);
    int getSku() const;
    std::string getName() const;
    double getPrice() const;
};

class ProductFactory {
public:
    static Product* createProduct(int sku);
};

#endif

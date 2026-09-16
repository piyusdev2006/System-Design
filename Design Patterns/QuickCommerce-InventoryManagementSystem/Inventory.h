#ifndef INVENTORY_H
#define INVENTORY_H

#include "Product.h"
#include <map>
#include <vector>

class InventoryStore {
public:
    virtual ~InventoryStore() = default;
    virtual void addProduct(Product* product, int quantity) = 0;
    virtual void removeProduct(int sku, int quantity) = 0;
    virtual int checkStock(int sku) const = 0;
    virtual std::vector<Product*> listAvailableProducts() const = 0;
};

class DbInventoryStore : public InventoryStore {
private:
    std::map<int, int> stock;
    std::map<int, Product*> products;

public:
    ~DbInventoryStore() override;
    void addProduct(Product* product, int quantity) override;
    void removeProduct(int sku, int quantity) override;
    int checkStock(int sku) const override;
    std::vector<Product*> listAvailableProducts() const override;
};

class InventoryManager {
private:
    InventoryStore* store;

public:
    explicit InventoryManager(InventoryStore* inventoryStore);
    ~InventoryManager();
    void addStock(int sku, int quantity);
    void removeStock(int sku, int quantity);
    int checkStock(int sku) const;
    std::vector<Product*> getAvailableProducts() const;
};

#endif

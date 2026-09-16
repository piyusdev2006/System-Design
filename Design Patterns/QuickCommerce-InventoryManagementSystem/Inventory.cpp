#include "Inventory.h"
#include <iostream>

DbInventoryStore::~DbInventoryStore() {
    for (auto& entry : products) {
        delete entry.second;
    }
}

void DbInventoryStore::addProduct(Product* product, int quantity) {
    int sku = product->getSku();
    if (products.count(sku) == 0) {
        products[sku] = product;
    } else {
        delete product;
    }
    stock[sku] += quantity;
}

void DbInventoryStore::removeProduct(int sku, int quantity) {
    auto found = stock.find(sku);
    if (found == stock.end()) {
        return;
    }

    int remaining = found->second - quantity;
    if (remaining > 0) {
        found->second = remaining;
    } else {
        stock.erase(found);
    }
}

int DbInventoryStore::checkStock(int sku) const {
    auto found = stock.find(sku);
    return found == stock.end() ? 0 : found->second;
}

std::vector<Product*> DbInventoryStore::listAvailableProducts() const {
    std::vector<Product*> available;
    for (const auto& entry : stock) {
        if (entry.second > 0 && products.count(entry.first) != 0) {
            available.push_back(products.at(entry.first));
        }
    }
    return available;
}

InventoryManager::InventoryManager(InventoryStore* inventoryStore)
    : store(inventoryStore) {}

InventoryManager::~InventoryManager() {
    delete store;
}

void InventoryManager::addStock(int sku, int quantity) {
    store->addProduct(ProductFactory::createProduct(sku), quantity);
    std::cout << "[InventoryManager] Added SKU " << sku
              << " Qty " << quantity << std::endl;
}

void InventoryManager::removeStock(int sku, int quantity) {
    store->removeProduct(sku, quantity);
}

int InventoryManager::checkStock(int sku) const {
    return store->checkStock(sku);
}

std::vector<Product*> InventoryManager::getAvailableProducts() const {
    return store->listAvailableProducts();
}

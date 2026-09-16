#ifndef DARK_STORE_H
#define DARK_STORE_H

#include "Inventory.h"
#include "Replenishment.h"
#include <map>
#include <string>
#include <vector>

class DarkStore {
private:
    std::string name;
    double x;
    double y;
    InventoryManager* inventoryManager;
    ReplenishStrategy* replenishStrategy;

public:
    DarkStore(std::string storeName, double xCoordinate, double yCoordinate);
    ~DarkStore();
    double distanceTo(double userX, double userY) const;
    void runReplenishment(const std::map<int, int>& itemsToReplenish);
    std::vector<Product*> getAllProducts() const;
    int checkStock(int sku) const;
    void removeStock(int sku, int quantity);
    void addStock(int sku, int quantity);
    void setReplenishStrategy(ReplenishStrategy* strategy);
    std::string getName() const;
    double getXCoordinate() const;
    double getYCoordinate() const;
    InventoryManager* getInventoryManager() const;
};

class DarkStoreManager {
private:
    std::vector<DarkStore*> darkStores;
    static DarkStoreManager* instance;
    DarkStoreManager() = default;

public:
    static DarkStoreManager* getInstance();
    ~DarkStoreManager();
    void registerDarkStore(DarkStore* darkStore);
    std::vector<DarkStore*> getNearbyDarkStores(
        double userX, double userY, double maxDistance) const;
};

#endif

#include "DarkStore.h"
#include <algorithm>
#include <cmath>
#include <utility>

DarkStore::DarkStore(std::string storeName, double xCoordinate, double yCoordinate)
    : name(std::move(storeName)), x(xCoordinate), y(yCoordinate),
      inventoryManager(new InventoryManager(new DbInventoryStore())),
      replenishStrategy(nullptr) {}

DarkStore::~DarkStore() {
    delete inventoryManager;
    delete replenishStrategy;
}

double DarkStore::distanceTo(double userX, double userY) const {
    return std::sqrt((x - userX) * (x - userX) +
                     (y - userY) * (y - userY));
}

void DarkStore::runReplenishment(
    const std::map<int, int>& itemsToReplenish) {
    if (replenishStrategy != nullptr) {
        replenishStrategy->replenish(inventoryManager, itemsToReplenish);
    }
}

std::vector<Product*> DarkStore::getAllProducts() const {
    return inventoryManager->getAvailableProducts();
}

int DarkStore::checkStock(int sku) const {
    return inventoryManager->checkStock(sku);
}

void DarkStore::removeStock(int sku, int quantity) {
    inventoryManager->removeStock(sku, quantity);
}

void DarkStore::addStock(int sku, int quantity) {
    inventoryManager->addStock(sku, quantity);
}

void DarkStore::setReplenishStrategy(ReplenishStrategy* strategy) {
    delete replenishStrategy;
    replenishStrategy = strategy;
}

std::string DarkStore::getName() const { return name; }
double DarkStore::getXCoordinate() const { return x; }
double DarkStore::getYCoordinate() const { return y; }
InventoryManager* DarkStore::getInventoryManager() const {
    return inventoryManager;
}

DarkStoreManager* DarkStoreManager::instance = nullptr;

DarkStoreManager* DarkStoreManager::getInstance() {
    if (instance == nullptr) {
        instance = new DarkStoreManager();
    }
    return instance;
}

DarkStoreManager::~DarkStoreManager() {
    for (DarkStore* darkStore : darkStores) {
        delete darkStore;
    }
    instance = nullptr;
}

void DarkStoreManager::registerDarkStore(DarkStore* darkStore) {
    darkStores.push_back(darkStore);
}

std::vector<DarkStore*> DarkStoreManager::getNearbyDarkStores(
    double userX, double userY, double maxDistance) const {
    std::vector<std::pair<double, DarkStore*>> distances;
    for (DarkStore* darkStore : darkStores) {
        double distance = darkStore->distanceTo(userX, userY);
        if (distance <= maxDistance) {
            distances.push_back({distance, darkStore});
        }
    }

    std::sort(distances.begin(), distances.end(),
              [](const auto& first, const auto& second) {
                  return first.first < second.first;
              });

    std::vector<DarkStore*> result;
    for (const auto& entry : distances) {
        result.push_back(entry.second);
    }
    return result;
}

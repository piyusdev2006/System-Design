#include "Replenishment.h"
#include "Inventory.h"
#include <iostream>

ThresholdReplenishStrategy::ThresholdReplenishStrategy(int value)
    : threshold(value) {}

void ThresholdReplenishStrategy::replenish(
    InventoryManager* manager,
    const std::map<int, int>& itemsToReplenish) {
    std::cout << "[ThresholdReplenish] Checking threshold... \n";
    for (const auto& item : itemsToReplenish) {
        int sku = item.first;
        int current = manager->checkStock(sku);
        if (current < threshold) {
            manager->addStock(sku, item.second);
            std::cout << "  -> SKU " << sku << " was " << current
                      << ", replenished by " << item.second << std::endl;
        }
    }
}

void WeeklyReplenishStrategy::replenish(
    InventoryManager* /*manager*/,
    const std::map<int, int>& /*itemsToReplenish*/) {
    std::cout << "[WeeklyReplenish] Weekly replenishment triggered for inventory.\n";
}

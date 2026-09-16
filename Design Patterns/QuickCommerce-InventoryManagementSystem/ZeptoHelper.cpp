#include "ZeptoHelper.h"
#include "DarkStore.h"
#include <iostream>
#include <map>

void ZeptoHelper::showAllItems(User* user) {
    std::cout << "\n[Zepto] All Available products within 5 KM for "
              << user->name << ":\n";
    auto nearbyStores =
        DarkStoreManager::getInstance()->getNearbyDarkStores(user->x, user->y, 5.0);
    std::map<int, double> prices;
    std::map<int, std::string> names;

    for (DarkStore* store : nearbyStores) {
        for (Product* product : store->getAllProducts()) {
            if (prices.count(product->getSku()) == 0) {
                prices[product->getSku()] = product->getPrice();
                names[product->getSku()] = product->getName();
            }
        }
    }

    for (const auto& item : prices) {
        std::cout << "  SKU " << item.first << " - " << names[item.first]
                  << " @ ₹" << item.second << "\n";
    }
}

void ZeptoHelper::initialize() {
    auto manager = DarkStoreManager::getInstance();

    auto darkStoreA = new DarkStore("DarkStoreA", 0.0, 0.0);
    darkStoreA->setReplenishStrategy(new ThresholdReplenishStrategy(3));
    std::cout << "\nAdding stocks in DarkStoreA...." << std::endl;
    darkStoreA->addStock(101, 5);
    darkStoreA->addStock(102, 2);

    auto darkStoreB = new DarkStore("DarkStoreB", 4.0, 1.0);
    darkStoreB->setReplenishStrategy(new ThresholdReplenishStrategy(3));
    std::cout << "\nAdding stocks in DarkStoreB...." << std::endl;
    darkStoreB->addStock(101, 3);
    darkStoreB->addStock(103, 10);

    auto darkStoreC = new DarkStore("DarkStoreC", 2.0, 3.0);
    darkStoreC->setReplenishStrategy(new ThresholdReplenishStrategy(3));
    std::cout << "\nAdding stocks in DarkStoreC...." << std::endl;
    darkStoreC->addStock(102, 5);
    darkStoreC->addStock(201, 7);

    manager->registerDarkStore(darkStoreA);
    manager->registerDarkStore(darkStoreB);
    manager->registerDarkStore(darkStoreC);
}

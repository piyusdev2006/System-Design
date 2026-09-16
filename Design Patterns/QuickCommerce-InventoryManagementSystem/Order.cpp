#include "Order.h"
#include <iostream>
#include <map>

int Order::nextId = 1;
OrderManager* OrderManager::instance = nullptr;

Order::Order(User* orderUser)
    : orderId(nextId++), user(orderUser), totalAmount(0.0),
      discountAmount(0.0) {}

OrderManager::OrderManager() {
    riderMapping.addRider(new Rider("Rider-A", 0.5, 0.5));
    riderMapping.addRider(new Rider("Rider-B", 3.0, 2.0));
    riderMapping.addRider(new Rider("Rider-C", 4.0, 3.0));
}

Order::~Order() {
    for (auto& item : items) {
        delete item.first;
    }
    for (DeliveryPartner* partner : partners) {
        delete partner;
    }
}

OrderManager* OrderManager::getInstance() {
    if (instance == nullptr) {
        instance = new OrderManager();
    }
    return instance;
}

void OrderManager::placeOrder(User* user, Cart* cart,
                              const std::string& couponCode) {
    std::cout << "\n[OrderManager] Placing Order for: " << user->name << "\n";
    std::vector<std::pair<Product*, int>> requestedItems = cart->getItems();
    std::vector<DarkStore*> nearbyStores =
        DarkStoreManager::getInstance()->getNearbyDarkStores(user->x, user->y, 5.0);

    if (nearbyStores.empty()) {
        std::cout << "  No dark stores within 5 KM. Cannot fulfill order.\n";
        return;
    }

    DarkStore* firstStore = nearbyStores.front();
    bool allInFirst = true;
    for (const auto& item : requestedItems) {
        if (firstStore->checkStock(item.first->getSku()) < item.second) {
            allInFirst = false;
            break;
        }
    }

    Order* order = new Order(user);
    if (allInFirst) {
        std::cout << "  All items at: " << firstStore->getName() << "\n";
        for (const auto& item : requestedItems) {
            int sku = item.first->getSku();
            firstStore->removeStock(sku, item.second);
            order->items.push_back({ProductFactory::createProduct(sku), item.second});
        }
        order->totalAmount = cart->getTotal();
        Rider* rider = riderMapping.assignNearestRider(user->x, user->y);
        std::string riderName = rider == nullptr ? "Partner1" : rider->getName();
        order->partners.push_back(new DeliveryPartner(riderName));
        std::cout << "  Assigned Delivery Partner: " << riderName << "\n";
    } else {
        std::cout << "  Splitting order across stores...\n";
        std::map<int, int> remainingItems;
        for (const auto& item : requestedItems) {
            remainingItems[item.first->getSku()] = item.second;
        }

        int partnerId = 1;
        for (DarkStore* store : nearbyStores) {
            if (remainingItems.empty()) {
                break;
            }
            std::cout << "   Checking: " << store->getName() << "\n";
            bool assigned = false;
            std::vector<int> fulfilled;

            for (auto& item : remainingItems) {
                int available = store->checkStock(item.first);
                if (available <= 0) {
                    continue;
                }
                int taken = std::min(available, item.second);
                store->removeStock(item.first, taken);
                std::cout << "     " << store->getName() << " supplies SKU "
                          << item.first << " x" << taken << "\n";
                order->items.push_back(
                    {ProductFactory::createProduct(item.first), taken});
                if (item.second > taken) {
                    item.second -= taken;
                } else {
                    fulfilled.push_back(item.first);
                }
                assigned = true;
            }

            for (int sku : fulfilled) {
                remainingItems.erase(sku);
            }
            if (assigned) {
                Rider* rider = riderMapping.assignNearestRider(user->x, user->y);
                std::string partnerName =
                    rider == nullptr ? "Partner" + std::to_string(partnerId++)
                                      : rider->getName();
                order->partners.push_back(new DeliveryPartner(partnerName));
                std::cout << "     Assigned: " << partnerName << " for "
                          << store->getName() << "\n";
            }
        }

        if (!remainingItems.empty()) {
            std::cout << "  Could not fulfill:\n";
            for (const auto& item : remainingItems) {
                std::cout << "    SKU " << item.first << " x" << item.second << "\n";
            }
        }
        for (const auto& item : order->items) {
            order->totalAmount += item.first->getPrice() * item.second;
        }
    }

    double beforeDiscount = order->totalAmount;
    order->totalAmount =
        PaymentGateway::applyCouponAndPay(order->totalAmount, couponCode);
    order->discountAmount = beforeDiscount - order->totalAmount;

    std::cout << "\n[OrderManager] Order #" << order->orderId << " Summary:\n";
    std::cout << "  User: " << user->name << "\n  Items:\n";
    for (const auto& item : order->items) {
        std::cout << "    SKU " << item.first->getSku() << " ("
                  << item.first->getName() << ") x" << item.second
                  << " @ ₹" << item.first->getPrice() << "\n";
    }
    std::cout << "  Total: ₹" << order->totalAmount << "\n";
    if (order->discountAmount > 0) {
        std::cout << "  Discount: ₹" << order->discountAmount << "\n";
    }
    std::cout << "  Partners:\n";
    for (const auto* partner : order->partners) {
        std::cout << "    " << partner->name << "\n";
    }
    std::cout << std::endl;
    orders.push_back(order);
}

std::vector<Order*> OrderManager::getAllOrders() const {
    return orders;
}

OrderManager::~OrderManager() {
    for (Order* order : orders) {
        delete order;
    }
    instance = nullptr;
}

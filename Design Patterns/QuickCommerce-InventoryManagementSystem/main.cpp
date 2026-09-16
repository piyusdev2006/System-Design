#include "Order.h"
#include "RiderMapping.h"
#include "ZeptoHelper.h"
#include <iostream>

int main() {
    ZeptoHelper::initialize();

    User* user = new User("Aditya", 1.0, 1.0);
    std::cout << "\nUser with name " << user->name
              << " comes on platform" << std::endl;

    ZeptoHelper::showAllItems(user);

    std::cout << "\nAdding items to cart\n";
    Cart* cart = user->getCart();
    cart->addItem(101, 4);
    cart->addItem(102, 3);
    cart->addItem(103, 2);

    OrderManager::getInstance()->placeOrder(user, cart, "SAVE10");

    delete user;
    delete OrderManager::getInstance();
    delete DarkStoreManager::getInstance();
    return 0;
}

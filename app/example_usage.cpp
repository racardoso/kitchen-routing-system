/**
 * Library example 
 * 
 * Simulate two PoS (Point of Sales) making orders to the system.
 * 
 */

#include "Kitchen.hpp"
#include "KitchenArea.hpp"
#include "Menu.hpp"
#include "Order.hpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main (void) {
    rdi::Kitchen kitchen; /* Create a kitchen.  */
    std::vector<std::string> areas({"Desserts", "Drinks", "Salad", "Grill", "Fries"});

    /* Create kitchen areas (fries, grill, salad, drink, desert).  */
    auto desserts = std::make_unique<rdi::KitchenArea>(areas[0]);
    auto drinks   = std::make_unique<rdi::KitchenArea>(areas[1]);
    auto salad    = std::make_unique<rdi::KitchenArea>(areas[2]);
    auto grill    = std::make_unique<rdi::KitchenArea>(areas[3]);
    auto fries    = std::make_unique<rdi::KitchenArea>(areas[4]);

    /* Create a couple of items.  */
    desserts->getMenu().addItem("Ice Cream", 12.32);
    desserts->getMenu().addItem("Apple Pie", 32.45);

    drinks->getMenu().addItem("Soda", 8.0);
    drinks->getMenu().addItem("Beer", 10.0);

    salad->getMenu().addItem("Ceasar Salad", 12.99);

    grill->getMenu().addItem("Royal with Cheese", 23.24);
    grill->getMenu().addItem("Big Kahuna", 22.34);

    fries->getMenu().addItem("Big Fries", 9.25);

    kitchen.addKitchenArea(std::move(desserts));
    kitchen.addKitchenArea(std::move(drinks));
    kitchen.addKitchenArea(std::move(salad));
    kitchen.addKitchenArea(std::move(grill));
    kitchen.addKitchenArea(std::move(fries));

    /* Creates two PoS (Point of Sale) 1 and simulate orders.  */
    std::thread pos1([&kitchen]() {
        for (int i = 0; i < 5; ++i) {
            rdi::Order o(i);
            o.addItemToOrder("Desserts", 1, 1);
            o.addItemToOrder("Grill", 1, 3);
            o.addItemToOrder("Fries", 1, 1);
            bool ret = kitchen.submitOrder(o); /* Ignore return.  */
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    /* Creates two PoS (Point of Sale) 2 and simulate orders.  */
    std::thread pos2([&kitchen]() {
        for (int i = 5; i < 10; ++i) {
            rdi::Order o(i);
            o.addItemToOrder("Grill", 2, 1);
            o.addItemToOrder("Drinks", 1, 2);
            o.addItemToOrder("Desserts", 1, 1);
            o.addItemToOrder("Salad", 1, 1);
            bool ret = kitchen.submitOrder(o);  /* Ignore return.  */
            std::this_thread::sleep_for(std::chrono::milliseconds(120));
        }
    });

    pos1.join();
    pos2.join();

    /* Take one OrderItem from Kitchen and print.  */
    for (const auto& area : areas) {
        rdi::KitchenArea* areaPtr = kitchen.getKitchenArea(area);
        if (areaPtr) {
            auto orderItem = areaPtr->takeOrderItem();
            if (auto item = areaPtr->getMenu().getItem(orderItem->m_itemId)) {
                std::cout << item->getName() << " -- " << item->getPrice()
                << " X" << orderItem->m_quantity << "\n";
            }
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}
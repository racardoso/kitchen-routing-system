/**
 *  TINY KITCHEN SYSTEM
 * 
 *  An usage example of RDI Kitchen Routing System Library on a small system.
 * 
 * */

#include "Kitchen.hpp"
#include "KitchenArea.hpp"
#include "Menu.hpp"
#include "Order.hpp"

#include <iostream>
#include <limits>
#include <memory>
#include <string>

static unsigned order_id_counter = 0; /* Simulate a auto id system.  */

void clear_cin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void create_area(rdi::Kitchen& kitchen) {
    std::cout << "Enter new kitchen area name: ";
    std::string area_name;
    std::getline(std::cin, area_name);

    auto area = std::make_unique<rdi::KitchenArea>(area_name);
    kitchen.addKitchenArea(std::move(area));
    std::cout << "\nAdded kitchen area: " << area_name << "\n";
}

void add_item_to_menu(rdi::KitchenArea* area_ptr) {
    std::string item_name;
    double price;
    std::cout << "\nEnter item name: ";
    std::getline(std::cin, item_name);
    std::cout << "\nEnter price: ";
    std::cin >> price;
    clear_cin();
    area_ptr->getMenu().addItem(item_name, price);
    std::cout << "\nItem added.\n";    
}

void remove_item_from_menu(rdi::KitchenArea* area_ptr) {
    unsigned long id;
    std::cout << "Enter item ID to remove: ";
    std::cin >> id;
    clear_cin();
    if (area_ptr->getMenu().removeItem(id)) {
        std::cout << "\nItem removed.\n";
    } else {
        std::cerr << "\nError: Item not found.\n";
    }
}

void edit_menu(rdi::Kitchen& kitchen) {
    std::cout << "Enter kitchen area name: ";
    std::string area_name;
    std::getline(std::cin, area_name);

    auto area_ptr= kitchen.getKitchenArea(area_name);

    if (!area_ptr) {
        std::cerr << "Error: kitchen area not found.\n";
        return;
    }
    for (;;) {
        std::cout << "\n===Edit Menu [" << area_name << "]===\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. Remove Item\n";
        std::cout << "3. Display Menu\n";
        std::cout << "4. Back\n";

        int choice;
        std::cin >> choice;
        clear_cin();

        switch (choice) {
            case 1:
                add_item_to_menu(area_ptr);
            break;
            case 2:
                remove_item_from_menu(area_ptr);
            break;
            case 3:
                area_ptr->getMenu().displayMenu();
            break;
            case 4:
                return;
            default:
                std::cerr << "\nError: invalid option\n";
        }
    }
}

void show_menus(rdi::Kitchen& kitchen) {
    for (const auto& [name, _] : kitchen.getAreas()) {
        auto area_ptr = kitchen.getKitchenArea(name);
        std::cout << "\nMenu for " << name << ":\n";
        area_ptr->getMenu().displayMenu();
    }
}

void make_an_order(rdi::Kitchen& kitchen) {
    order_id_counter += 1;
    rdi::Order order(order_id_counter);

    for (;;) {
        /* FIXME: Use a key like ESC to exit. */
        std::cout <<  "\nEnter kitchen area (or enter 'exit' to leave): ";
        std::string area_name;
        std::getline(std::cin, area_name);

        if (area_name == "exit") {
            break;
        }
        /* FIXME: Should move this to a function. */
        auto area_ptr = kitchen.getKitchenArea(area_name);
        if (!area_ptr) {
            std::cerr << "\nError: Invalid kitchen area\n";
            continue;
        }
        unsigned long item_id;
        unsigned quantity;
        std::cout << "\nEnter item ID: ";
        std::cin >> item_id;
        std::cout << "\nEnter quantity: ";
        std::cin >> quantity;
        clear_cin();

        if (!area_ptr->getMenu().hasItem(item_id)) {
            std::cerr << "\nError: Item not found.\n";
            continue;
        }
        order.addItemToOrder(area_name, item_id, quantity);
    }
    if (kitchen.submitOrder(order)) {
        std::cout << "\nOrder " << order_id_counter << " submitted to kitchen.\n";
     } else {
        std::cerr << "\nError: Order " << order_id_counter << "is invalid.\n";
     }
}

void take_an_order(rdi::Kitchen& kitchen){
    std::cout << "Enter Kitchen Area: ";
    std::string area_name;
    std::getline(std::cin, area_name);

    auto area_ptr = kitchen.getKitchenArea(area_name);
    if (!area_ptr) {
        std::cerr << "\nError: Invalid kitchen area.\n";
        return;
    }

    auto order_item = area_ptr->takeOrderItem();
    if (order_item) {
        auto item = area_ptr->getMenu().getItem(order_item->m_itemId);
        if (item) {
            std::cout << "\nTake order item: " << item->getName() << " X"
            << order_item->m_quantity << " (" << area_name << ")\n";
        } else {
            /* An invalid item means an internal error occured.  */
            std::cerr << "\nInternal Error: Something went wrong\n";  
        } 
    } else {
        std::cout << "\nNo orders in: " << area_name << ".\n";
    }
}

void show_kitchen_areas(rdi::Kitchen& kitchen) {
    std::cout << "Kitchen Areas: \n";
    for (const auto& [name, _] : kitchen.getAreas()) {
        auto area_ptr = kitchen.getKitchenArea(name);
        std::cout << name << ":\n";
    }
}

void show_main_menu() {
    std::cout << "\n========= TINY KITCHEN SYSTEM =========\n";
    std::cout << "1. Create New Kitchen\n";
    std::cout << "2. Add Kitchen Area\n";
    std::cout << "3. Show Kitchen Areas\n";
    std::cout << "4. Edit Menu\n";
    std::cout << "5. Show Menus\n";
    std::cout << "6. Make an Order\n";
    std::cout << "7. Take Item from Kitchen\n";
    std::cout << "8. Exit\n";
    std::cout << "Select an option: ";
}

int main (void) {
    std::unique_ptr<rdi::Kitchen> kitchen; /* Create a kitchen. */

    for (;;) {
        show_main_menu();
        int choice = 0;
        std::cin >> choice;
        clear_cin();

        switch (choice) {
            case 1:
                kitchen = std::make_unique<rdi::Kitchen>();
                std::cout << "Created new Kitchen.\n";
            break;
            case 2:
                if (!kitchen) {
                    std::cerr << "Error: Must create a Kitchen first\n";
                } else {
                    create_area(*kitchen);
                }
            break;
            case 3:
                if (!kitchen) {
                    std::cerr << "Error: Must create a Kitchen first\n";
                } else {
                    show_kitchen_areas(*kitchen);
                }
            break;
            case 4:
                if (!kitchen) {
                    std::cerr << "Error: Must create a Kitchen first\n";
                } else {
                    edit_menu(*kitchen);
                }
            break;
            case 5:
                if (!kitchen) {
                    std::cerr << "Error: Must create a Kitchen first\n";
                } else {
                    show_menus(*kitchen);
                }
            break;
            case 6:
                if (!kitchen) {
                    std::cerr << "Error: Must create a Kitchen first\n";
                } else {
                    make_an_order(*kitchen);
                }
            break;
            case 7:
                if (!kitchen) {
                    std::cerr << "Error: Must create a Kitchen first\n";
                } else {
                    take_an_order(*kitchen);
                }
            break;            
            case 8:
                std::cout << "Exiting\n";
                return 0;
            default:
                std::cerr << "Error: Invalid option\n";
        }
    }

    return 0;
}
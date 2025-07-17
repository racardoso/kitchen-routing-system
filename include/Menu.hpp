/**
 * @file Kitchen.hpp
 * @brief Defines the Menu class.
 */

#pragma once
#ifndef __MENU_HPP__
#define __MENU_HPP__

#include <string>
#include <optional>
#include <unordered_map>

#include "Item.hpp"

/**
 * @namespace rdi
 * @brief RDI namespace.
 */
namespace rdi {

/**
 * @class Menu
 * @brief Represents a menu (collections) of items available in a kitchen area.
 *
 * The Menu holds a collection of items identified by a unique ID.
 */
class Menu {
public:
    Menu();
    /**
     * @brief Adds a new item to the menu.
     * @param name Name of the item.
     * @param price Price of the item.
     */
    void addItem(const std::string& name, double price);

    /**
     * @brief Removes an item from the menu.
     * @param id The ID of the item to remove.
     * @return True if the item was found and removed, false otherwise.
     */
    [[nodiscard]] bool removeItem(unsigned long id);

    /**
     * @brief Displays the menu items to stdout.
     */
    void displayMenu() const;

    /**
     * @brief Checks if an item exists in the menu.
     * @param id The ID of the item to check.
     * @return True if the item exists, false otherwise.
     */
    [[nodiscard]] bool hasItem(unsigned long id) const;

    /**
     * @brief Gets an item from menu.
     * @param id The ID of the item to get.
     * @return An optional containing the next item, or nullopt if item not found.
     */
    [[nodiscard]] std::optional<Item> getItem(unsigned long id);

private:
    std::unordered_map<unsigned long, Item> m_items;  /**< Map of Items. */
    unsigned long m_id = 0; /**< Internal counter for assigning unique IDs to the items. */
};

} // namespace rdi
#endif // __MENU_HPP__
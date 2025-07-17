/**
 * @file Item.hpp
 * @brief Defines the (Menu) Item class.
 */

#pragma once
#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <string>

/**
 * @namespace rdi
 * @brief RDI namespace.
 */
namespace rdi {

/**
 * @class Item
 * @brief Represents an item with a name and price.
 */
class Item {
public:
    /**
     * @brief Constructs an Item with the given name and price.
     * @param name The name of the item.
     * @param price The price of the item.
     */
    explicit Item(const std::string& name, double price);

    /**
     * @brief Retrieves the name of the item.
     * @return The name as a std::string.
     */
    [[nodiscard]] const std::string& getName() const;

    /**
     * @brief Retrieves the price of the item.
     * @return The price as a double.
     */
    [[nodiscard]] double getPrice() const;

    /**
     * @brief Updates the name and price of the item.
     * @param name The new name of the item.
     * @param price The new price of the item.
     */
    void updateItem(std::string_view name, double price);

private:
    std::string m_name; /**< The name of the item. */
    double m_price; /**< The price of the item. */
};

} // namespace rdi
#endif // __ITEM_HPP__
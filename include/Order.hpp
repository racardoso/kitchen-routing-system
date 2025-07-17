/**
 * @file Order.hpp
 * @brief Defines the Order class.
 */

#pragma once
#ifndef __ORDER_HPP__
#define __ORDER_HPP__

#include <string>
#include <vector>

/**
 * @namespace rdi
 * @brief RDI namespace.
 */
namespace rdi {

/**
 * @struct OrderItem
 * @brief Represents a single item in an order.
 */
struct OrderItem {
    std::string m_area;  /**< The name of the kitchen area (destination).  */
    unsigned long m_itemId = 0; /**< ID of the item ordered. */
    unsigned m_quantity = 0; /**< Quantity of the item ordered. */
    bool m_ready = false; /**< (Future usage): Flag to check if item is ready (processed). */

    /**
     * @brief Constructs an order item.
     * @param area Name of the kitchen area.
     * @param itemId ID of the item.
     * @param quantity Quantity ordered.
     */
    OrderItem(std::string_view area, unsigned long itemId, unsigned quantity);
};

/**
 * @class Order
 * @brief Represents an costumer order.
 *
 * An order holds multiple order items.
 */
class Order {
public:
    /**
     * @brief Constructs an order with a unique ID.
     * @param orderId The unique ID.
     */
    explicit Order(unsigned long orderId);
    
    /**
     * @brief Gets the order ID.
     * @return The order ID.
     */
    [[nodiscard]] unsigned long getOrderId() const;

    /**
     * @brief Adds an item to this order.
     * @param area The kitchen area where the item belongs.
     * @param itemId The ID of the item.
     * @param quantity Quantity ordered.
     */
    void addItemToOrder(std::string_view area, unsigned long itemId, unsigned quantity);

    /**
     * @brief Gets the list of items in this order.
     * @return A const reference to the vector of (order) items.
     */
    [[nodiscard]] const std::vector<OrderItem>& getOrderItems() const;

private:
    unsigned long m_orderId;
    std::vector<OrderItem> m_orderItems;
};

} // namespace rdi
#endif // __ORDER_HPP__
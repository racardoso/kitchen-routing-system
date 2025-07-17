/**
 * @file Kitchen.hpp
 * @brief Defines the Kitchen Area class.
 */

#pragma once
#ifndef __KITCHEN_AREA_HPP__
#define __KITCHEN_AREA_HPP__

#include <string>
#include <queue>
#include <mutex>
#include <optional>

#include "Order.hpp"
#include "Menu.hpp"

/**
 * @namespace rdi
 * @brief RDI namespace.
 */
namespace rdi {

/**
 * @class KitchenArea
 * @brief Represents a area in the kitchen responsible for handling orders.
 *
 * Every KitchenArea have its own menu and a (thread safe) queue of order items.
 */
class KitchenArea {
public:
    /**
     * @brief Constructs a KitchenArea.
     * @param name Name of the kitchen area (e.g. fries, grill, salad, drink, desert).
     */
    explicit KitchenArea(const std::string& name);

     /**
     * @brief Virtual destructor
     * Note: It is unclear if this class will need be specialized in the future, so lets
     * make this virtual in the case we have to derive from this.
     */
    virtual ~KitchenArea() = default;

    /**
     * @brief Gets the name of the kitchen area.
     * @return A const reference to the name of the kitchen area.
     */
     [[nodiscard]] const std::string& getName() const;

    /**
     * @brief Provides access to the menu of this kitchen area.
     * @return A reference to the menu.
     */
     [[nodiscard]] Menu& getMenu();

    /**
     * @brief Provides read-only access to the menu of this kitchen area.
     * @return A const reference to the menu.
     */
     [[nodiscard]]  const Menu& getMenu() const;

    /**
     * @brief Submits an order item to this kitchen area's queue.
     * @param order The order item to enqueue.
     */
    void submitOrder(const OrderItem& order);

    /**
     * @brief Retrieves and removes the next item from the queue.
     * @return An optional containing the next item, or nullopt if the queue is empty.
     */
     [[nodiscard]] std::optional<OrderItem> takeOrderItem();

private:
    std::string m_name; /**< Name of the kitchen area. */
    Menu m_menu;  /**< Menu of available items for this area. */
    std::mutex m_mutex; /**< Mutex to protect the order queue. */
    std::queue<OrderItem> m_orderItems; /**< Queue of order items (pending). */
};

} // namespace rdi
#endif // __KITCHEN_AREA_HPP__
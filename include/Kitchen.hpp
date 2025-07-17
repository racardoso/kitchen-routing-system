/**
 * @file Kitchen.hpp
 * @brief Defines the Kitchen class.
 */

#pragma once
#ifndef __KITCHEN_HPP__
#define __KITCHEN_HPP__

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>


#include "Order.hpp"
#include "KitchenArea.hpp"

/**
 * @namespace rdi
 * @brief RDI namespace.
 */
namespace rdi {

/**
 * @class Kitchen
 * @brief Represents the kitchen an it is responsible for route orders to the kitchen areas.
 *
 * The Kitchen maintains a queue of orders submitted by PoS (Poit of Sales) and a collection
 * of kitchen areas. An internal thread (routerOrder) runs in background and it is responsible
 * to send the orders to the kitchen area queues.
 */
class Kitchen {
public:
    /**
     * @brief Constructs Kitchen and starts routerOrder thread.
     */
    Kitchen();

    /**
     * @brief Destructor stops router thread and cleans up.
     */
    ~Kitchen();

    /**
     * @brief Adds a new kitchen area to the kitchen.
     * @param area Unique pointer to a KitchenArea instance.
     */
    // Note: a unique_ptr make senses if we ever want to extend KitchenArea and make
    // it polymorphic
    void addKitchenArea(std::unique_ptr<KitchenArea> area);

    /**
     * @brief Check if an order contains valid products for the existing kitchen area.
     * @param order The order to be validated.
     * @return true if the order is valid, false otherwise.
     */
    [[nodiscard]] bool isOrderValid(const Order& order);

    /**
     * @brief Submits an order to the kitchen.
     * @param order The order to be submitted.
     * @return True if the order was successfully queued, false otherwise.
     */
    [[nodiscard]] bool submitOrder(const Order& order);

    /**
     * @brief Retrieves a pointer to the KitchenArea by name.
     * @param name Name of the kitchen area.
     * @return Pointer to KitchenArea, or nullptr if not found.
     */
    [[nodiscard]] KitchenArea* getKitchenArea(const std::string& name);

    /**
     * @brief Get a const reference to the kitchen areas map.
     * @return const reference to the unordered_map of kitchen areas.
     */
    [[nodiscard]] const std::unordered_map<std::string, std::unique_ptr<KitchenArea>>& getAreas() const;

private:
    /**
     * @brief Thread loop that waits for orders and routes them to the appropriated kitchen areas.
     */
    void routerOrder();
    std::unordered_map<std::string, std::unique_ptr<KitchenArea>> m_areas; /**< Maps kitchen area name to KitchenArea instance. */
    std::queue<Order> m_orders; /**< Queue of orders waiting. */
    std::thread m_thread;  /**< Internal thread that routes orders. */
    std::mutex m_mutex; /**< Mutex for shared data structures. */
    std::condition_variable m_cv; /**< Condition variable that signal an order arrival. */
    bool m_stop = false; /**< Flag to stop router. */
};

} // namespace rdi
#endif // __KITCHEN_HPP__
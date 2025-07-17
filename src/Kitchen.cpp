#include "Kitchen.hpp"
#include "Order.hpp"

#include <string>
#include <thread>
#include <memory>

namespace rdi {

Kitchen::Kitchen() {
    m_thread = std::thread(&Kitchen::routerOrder, this);
}

Kitchen::~Kitchen() {
    {
        std::scoped_lock lock(m_mutex);
        m_stop = true;
        m_cv.notify_all();
    } // Release lock.
       
    if (m_thread.joinable()) {
         m_thread.join();
    }
}

void Kitchen::addKitchenArea(std::unique_ptr<KitchenArea> area) {
    std::scoped_lock lock(m_mutex);
    const std::string& areaName = area->getName();
    m_areas[areaName] = std::move(area);
}

bool Kitchen::isOrderValid(const Order& order) {
    for (const auto& orderItem : order.getOrderItems()) {
        auto it = m_areas.find(orderItem.m_area);
        if (it != m_areas.end()) {
            if (it->second->getMenu().hasItem(orderItem.m_itemId) == false) {
                return false; /* Product not found.  */
            }
        } else {
            return false; /* Invalid Menu/Kitchen Area.  */
        }
    }
    return true;
}

bool Kitchen::submitOrder(const Order& order) {
    if (!isOrderValid(order)) {
        return false;
    }
    {
        std::scoped_lock lock(m_mutex);
        m_orders.push(order);
        m_cv.notify_one();
    } // Release lock.
       
    return true;
}

void Kitchen::routerOrder() {
    // Wait for orders to route
    for (;;) {
        std::unique_lock lock(m_mutex);
        m_cv.wait(lock, [this]() { return !m_orders.empty() || m_stop; });

        if (m_stop && m_orders.empty())
            break;

        Order order = m_orders.front();
        m_orders.pop();
        lock.unlock();

        for (const auto& orderItem : order.getOrderItems()) {
            // The order is already valid just need to route to the area
            auto it = m_areas.find(orderItem.m_area);
            if (it != m_areas.end()) {
                it->second->submitOrder(orderItem);
            }
        }
    }
}

KitchenArea* Kitchen::getKitchenArea(const std::string& name) {
    std::scoped_lock lock(m_mutex);
    auto it = m_areas.find(name);
    if (it != m_areas.end()) {
        return it->second.get();
    }
    return nullptr;
}

const std::unordered_map<std::string, std::unique_ptr<KitchenArea>>&
rdi::Kitchen::getAreas() const {
    return m_areas;
}

} // namespace rdi

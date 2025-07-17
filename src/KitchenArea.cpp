#include "KitchenArea.hpp"
#include "Order.hpp"

#include <optional>
#include <string>
#include <mutex>

namespace rdi {

KitchenArea::KitchenArea(const std::string& name) : m_name(name) {}

const std::string& KitchenArea::getName() const { return m_name; }

Menu& KitchenArea::getMenu() { return m_menu; }

const Menu& KitchenArea::getMenu() const { return m_menu; }

// Enqueue the submited orders
void KitchenArea::submitOrder(const OrderItem& order) {
    std::scoped_lock lock(m_mutex);
    m_orderItems.push(order);
}

std::optional<OrderItem> KitchenArea::takeOrderItem() {
    std::scoped_lock lock(m_mutex);
    if (m_orderItems.empty()) {
        return std::nullopt;
    }
    auto item = m_orderItems.front();
    m_orderItems.pop();
    return item;
}
} // namespace rdi
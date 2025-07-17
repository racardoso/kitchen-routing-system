#include "Order.hpp"

#include <string>
#include <vector>

namespace rdi {

OrderItem::OrderItem(std::string_view area, unsigned long itemId, unsigned quantity) :
m_area(area), m_itemId(itemId), m_quantity(quantity) {}

Order::Order(unsigned long orderId) : m_orderId(orderId) {}

unsigned long Order::getOrderId() const { return m_orderId; }

void Order::addItemToOrder(std::string_view area, unsigned long itemId, unsigned quantity) {
        m_orderItems.emplace_back(area, itemId, quantity);
    }

const std::vector<OrderItem>& Order::getOrderItems() const {
    return m_orderItems;
}

} // namespace rdi
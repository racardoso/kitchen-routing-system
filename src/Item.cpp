#include "Item.hpp"

#include <string>

namespace rdi {

Item::Item(const std::string& name, double price) : m_name(name), m_price(price) {}

const std::string& Item::getName() const { return m_name; }

double Item::getPrice() const { return m_price; }

void Item::updateItem(std::string_view name, double price)  {
    m_name = name;
    m_price = price;
}

} // namespace rdi
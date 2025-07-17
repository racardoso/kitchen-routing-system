#include "Menu.hpp"

#include <iostream>
#include <string>

namespace rdi {
Menu::Menu() : m_id(0) {}

void Menu::addItem(const std::string& name, double price) {
    m_id += 1;
    m_items.try_emplace(m_id, name, price);
}

bool Menu::removeItem(unsigned long id) {
    if (hasItem(id)) {
        m_items.erase(id);
        return true;
    } else {
        return false;
    }
}

void Menu::displayMenu() const {
    for (const auto& [id, item] : m_items) {
        std::cout << id << ": " << item.getName() << "\n";
    }
}

bool Menu::hasItem(unsigned long id) const {
    return m_items.count(id) != 0;
}

std::optional<Item> Menu::getItem(unsigned long id) {
    auto it = m_items.find(id);
    if (it != m_items.end()) {
        return it->second;
    }

    return std::nullopt;
}

} // namespace rd1

#pragma once

#include <array>
#include <string>
#include <string_view>

class Inventory
{
private:
    static constexpr int MAX_ITEMS = 5;

    std::array<std::string, MAX_ITEMS> m_items{};
    int m_itemsCount{ 0 };
    std::string m_talisman{};

public:
    explicit Inventory(int initialItemsCount = 0);
    ~Inventory();

    bool AddItem(std::string_view itemName);
    bool RemoveItem(std::string_view itemName);
    bool EquipTalisman(std::string_view talismanName);

    void ShowInfo() const;

    int GetItemsCount() const;
    std::string_view GetTalisman() const;
};

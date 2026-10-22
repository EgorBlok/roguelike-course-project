
#include "Inventory.hpp"

#include <iostream>

Inventory::Inventory(int initialItemsCount)
{
    if (initialItemsCount >= 0 && initialItemsCount <= MAX_ITEMS)
    {
        m_itemsCount = initialItemsCount;

        for (int i = 0; i < m_itemsCount; ++i)
        {
            m_items[i] = "Начальный предмет";
        }
    }

    std::cout << "[Inventory] Инвентарь создан\n";
}

Inventory::~Inventory()
{
    std::cout << "[Inventory] Инвентарь уничтожен\n";
}

bool Inventory::AddItem(std::string_view itemName)
{
    if (itemName.empty() || m_itemsCount >= MAX_ITEMS)
    {
        std::cout << "Нельзя добавить предмет\n";
        return false;
    }

    m_items[m_itemsCount] = itemName;
    ++m_itemsCount;

    std::cout << "Добавлен предмет: " << itemName << '\n';
    return true;
}

bool Inventory::RemoveItem(std::string_view itemName)
{
    for (int i = 0; i < m_itemsCount; ++i)
    {
        if (m_items[i] == itemName)
        {
            for (int j = i; j < m_itemsCount - 1; ++j)
            {
                m_items[j] = m_items[j + 1];
            }

            --m_itemsCount;
            m_items[m_itemsCount].clear();

            std::cout << "Удалён предмет: " << itemName << '\n';
            return true;
        }
    }

    std::cout << "Предмет не найден\n";
    return false;
}

bool Inventory::EquipTalisman(std::string_view talismanName)
{
    if (talismanName.empty())
    {
        std::cout << "Некорректное название талисмана\n";
        return false;
    }

    if (!m_talisman.empty())
    {
        std::cout << "Замена талисмана: " << m_talisman
                  << " -> " << talismanName << '\n';
    }

    m_talisman = talismanName;

    std::cout << "Активный талисман: " << m_talisman << '\n';
    return true;
}

void Inventory::ShowInfo() const
{
    std::cout << "\n--- Инвентарь ---\n";
    std::cout << "Предметы: " << m_itemsCount
              << "/" << MAX_ITEMS << '\n';

    for (int i = 0; i < m_itemsCount; ++i)
    {
        std::cout << i + 1 << ". " << m_items[i] << '\n';
    }

    if (m_talisman.empty())
    {
        std::cout << "Талисман: отсутствует\n";
    }
    else
    {
        std::cout << "Талисман: " << m_talisman << '\n';
    }
}

int Inventory::GetItemsCount() const
{
    return m_itemsCount;
}

std::string_view Inventory::GetTalisman() const
{
    return m_talisman;
}

#include "Hero.hpp"

#include <iostream>

Hero::Hero(std::string_view name, int maxHealth, int attack)
    : BaseCharacter{ name.empty() ? std::string_view{ "Безымянный герой" } : name,
                     maxHealth, attack }
{
    std::cout << "[Hero] Герой создан: " << GetName() << '\n';
}

Hero::~Hero()
{
    std::cout << "[Hero] Герой уничтожается: " << GetName() << '\n';
}

void Hero::Heal(int amount)
{
    if (!IsAlive())
    {
        std::cout << "Нельзя лечить погибшего героя\n";
        return;
    }

    if (amount <= 0 || GetHealth() == GetMaxHealth())
    {
        std::cout << "Лечение невозможно\n";
        return;
    }

    RestoreHealth(amount);
    std::cout << GetName() << " восстанавливает здоровье: "
              << GetHealth() << "/" << GetMaxHealth() << '\n';
}

void Hero::AttackEnemy()
{
    if (!IsAlive())
    {
        std::cout << "Погибший герой не может атаковать\n";
        return;
    }

    // Слабая ссылка не владеет противником.
    const std::shared_ptr<Enemy> enemy = m_enemy.lock();
    if (!enemy)
    {
        std::cout << "Нет текущего противника (или он уничтожен)\n";
        return;
    }

    if (!enemy->IsAlive())
    {
        std::cout << "Противник уже побеждён\n";
        return;
    }

    std::cout << GetName() << " атакует " << enemy->GetName() << '\n';
    enemy->TakeDamage(GetAttack());
}

void Hero::SetEnemy(const std::shared_ptr<Enemy>& enemy)
{
    m_enemy = enemy;

    if (enemy)
    {
        std::cout << "Текущий противник: " << enemy->GetName() << '\n';
    }
    else
    {
        std::cout << "Текущий противник отсутствует\n";
    }
}

void Hero::AddCoins(int amount)
{
    if (amount <= 0)
    {
        std::cout << "Некорректное количество монет\n";
        return;
    }

    m_coins += amount;
    std::cout << "Получено монет: " << amount
              << ". Всего: " << m_coins << '\n';
}

std::string_view Hero::GetRole() const
{
    return "Герой";
}

void Hero::ShowInfo() const
{
    std::cout << "\n--- " << GetRole() << " ---\n"
              << GetBaseInfo() << '\n'
              << "Монеты: " << m_coins << '\n';
    m_inventory.ShowInfo();
}

int Hero::GetCoins() const
{
    return m_coins;
}

Inventory& Hero::GetInventory()
{
    return m_inventory;
}

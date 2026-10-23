
#include "Hero.hpp"

#include <algorithm>
#include <iostream>

Hero::Hero(std::string_view name, int maxHealth, int attack)
    : m_name{ name }
    , m_maxHealth{ std::max(1, maxHealth) }
    , m_health{ m_maxHealth }
    , m_attack{ std::max(1, attack) }
{
    if (m_name.empty())
    {
        m_name = "Безымянный герой";
    }

    std::cout << "[Hero] Герой создан: " << m_name << '\n';
}

Hero::~Hero()
{
    std::cout << "[Hero] Герой уничтожается: " << m_name << '\n';
}

void Hero::TakeDamage(int damage)
{
    if (!IsAlive())
    {
        std::cout << m_name << " уже побеждён\n";
        return;
    }

    if (damage <= 0)
    {
        std::cout << "Некорректный урон\n";
        return;
    }

    m_health = std::max(0, m_health - damage);

    std::cout << m_name << " получает " << damage
              << " урона. Здоровье: "
              << m_health << "/" << m_maxHealth << '\n';

    if (!IsAlive())
    {
        std::cout << m_name << " погиб!\n";
    }
}

void Hero::Heal(int amount)
{
    if (!IsAlive())
    {
        std::cout << "Нельзя лечить погибшего героя\n";
        return;
    }

    if (amount <= 0 || m_health == m_maxHealth)
    {
        std::cout << "Лечение невозможно\n";
        return;
    }

    m_health += std::min(amount, m_maxHealth - m_health);

    std::cout << m_name << " восстанавливает здоровье: "
              << m_health << "/" << m_maxHealth << '\n';
}

void Hero::AttackEnemy()
{
    if (!IsAlive())
    {
        std::cout << "Погибший герой не может атаковать\n";
        return;
    }

    if (m_enemy == nullptr)
    {
        std::cout << "Нет текущего противника\n";
        return;
    }

    if (!m_enemy->IsAlive())
    {
        std::cout << "Противник уже побеждён\n";
        return;
    }

    std::cout << m_name << " атакует "
              << m_enemy->GetName() << '\n';

    m_enemy->TakeDamage(m_attack);
}

void Hero::SetEnemy(Enemy* enemy)
{
    m_enemy = enemy;

    if (m_enemy != nullptr)
    {
        std::cout << "Текущий противник: "
                  << m_enemy->GetName() << '\n';
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

void Hero::ShowInfo() const
{
    std::cout << "\n--- Герой ---\n";
    std::cout << "Имя: " << m_name << '\n';
    std::cout << "Здоровье: " << m_health
              << "/" << m_maxHealth << '\n';
    std::cout << "Атака: " << m_attack << '\n';
    std::cout << "Монеты: " << m_coins << '\n';

    m_inventory.ShowInfo();
}

bool Hero::IsAlive() const
{
    return m_health > 0;
}

int Hero::GetHealth() const
{
    return m_health;
}

int Hero::GetCoins() const
{
    return m_coins;
}

Inventory& Hero::GetInventory()
{
    return m_inventory;
}

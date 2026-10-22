
#include "Enemy.hpp"

#include <algorithm>
#include <iostream>

Enemy::Enemy(std::string_view name, int maxHealth, int attack)
    : m_name{ name }
    , m_maxHealth{ std::max(1, maxHealth) }
    , m_health{ m_maxHealth }
    , m_attack{ std::max(1, attack) }
{
    if (m_name.empty())
    {
        m_name = "Неизвестный противник";
    }

    std::cout << "[Enemy] Создан противник: " << m_name << '\n';
}

Enemy::~Enemy()
{
    std::cout << "[Enemy] Уничтожен противник: " << m_name << '\n';
}

void Enemy::TakeDamage(int damage)
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
        std::cout << m_name << " побеждён!\n";
    }
}

int Enemy::Attack() const
{
    if (!IsAlive())
    {
        std::cout << m_name << " не может атаковать\n";
        return 0;
    }

    std::cout << m_name << " атакует! Урон: "
              << m_attack << '\n';

    return m_attack;
}

bool Enemy::IsAlive() const
{
    return m_health > 0;
}

void Enemy::ShowInfo() const
{
    std::cout << "\n--- Противник ---\n";
    std::cout << "Имя: " << m_name << '\n';
    std::cout << "Здоровье: " << m_health
              << "/" << m_maxHealth << '\n';
    std::cout << "Атака: " << m_attack << '\n';

    std::cout << "Состояние: "
              << (IsAlive() ? "жив" : "побеждён")
              << '\n';
}

std::string_view Enemy::GetName() const
{
    return m_name;
}

int Enemy::GetHealth() const
{
    return m_health;
}

int Enemy::GetMaxHealth() const
{
    return m_maxHealth;
}

#include "BaseCharacter.hpp"

#include <algorithm>
#include <iostream>
#include <string>

BaseCharacter::BaseCharacter(std::string_view name, int maxHealth, int attack)
    : m_name{ name.empty() ? "Неизвестный персонаж" : std::string{ name } }
    , m_maxHealth{ std::max(1, maxHealth) }
    , m_health{ m_maxHealth }
    , m_attack{ std::max(1, attack) }
{
    std::cout << "[BaseCharacter] Создана базовая часть: " << m_name << '\n';
}

BaseCharacter::~BaseCharacter()
{
    std::cout << "[BaseCharacter] Уничтожена базовая часть: " << m_name << '\n';
}

void BaseCharacter::TakeDamage(int damage)
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
              << " урона. Здоровье: " << m_health
              << "/" << m_maxHealth << '\n';

    if (!IsAlive())
    {
        std::cout << m_name << " побеждён!\n";
    }
}

void BaseCharacter::RestoreHealth(int amount)
{
    if (IsAlive() && amount > 0)
    {
        m_health += std::min(amount, m_maxHealth - m_health);
    }
}

bool BaseCharacter::IsAlive() const
{
    return m_health > 0;
}

std::string_view BaseCharacter::GetName() const
{
    return m_name;
}

int BaseCharacter::GetHealth() const
{
    return m_health;
}

int BaseCharacter::GetMaxHealth() const
{
    return m_maxHealth;
}

int BaseCharacter::GetAttack() const
{
    return m_attack;
}

std::string BaseCharacter::GetBaseInfo() const
{
    return "Имя: " + m_name
        + "\nЗдоровье: " + std::to_string(m_health)
        + "/" + std::to_string(m_maxHealth)
        + "\nАтака: " + std::to_string(m_attack);
}

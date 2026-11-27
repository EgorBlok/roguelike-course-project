#include "BaseCharacter.hpp"

#include <algorithm>
#include <iostream>
#include <utility>

int BaseCharacter::NextId()
{
    return ++s_createdCount;
}

BaseCharacter::BaseCharacter(std::string_view name, int maxHealth, int attack)
    : m_id{ NextId() }
    , m_name{ name.empty() ? "Без имени" : std::string{ name } }
    , m_healthState{ std::make_shared<HealthState>(HealthState{
          std::max(1, maxHealth), std::max(1, maxHealth) }) }
    , m_attack{ std::max(1, attack) }
{
    std::cout << "[BaseCharacter] Конструктор: " << m_name << '\n';
}

// Глубокое копирование: у копии собственный HealthState.
BaseCharacter::BaseCharacter(const BaseCharacter& other)
    : m_id{ NextId() }
    , m_name{ other.m_name }
    , m_healthState{ std::make_shared<HealthState>(*other.m_healthState) }
    , m_attack{ other.m_attack }
{
    std::cout << "[BaseCharacter] Копирование: " << m_name << '\n';
}

BaseCharacter::BaseCharacter(BaseCharacter&& other) noexcept
    : m_id{ NextId() }
    , m_name{ std::move(other.m_name) }
    , m_healthState{ std::move(other.m_healthState) }
    , m_attack{ other.m_attack }
{
    std::cout << "[BaseCharacter] Перемещение: " << m_name << '\n';
}

BaseCharacter::~BaseCharacter()
{
    std::cout << "[BaseCharacter] Деструктор: " << m_name << '\n';
}

BaseCharacter& BaseCharacter::operator=(const BaseCharacter& other)
{
    if (this == &other)
    {
        return *this;
    }

    auto newHealthState = std::make_shared<HealthState>(*other.m_healthState);
    m_name = other.m_name;
    m_attack = other.m_attack;
    m_healthState = std::move(newHealthState);
    return *this;
}

BaseCharacter& BaseCharacter::operator=(BaseCharacter&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    m_name = std::move(other.m_name);
    m_healthState = std::move(other.m_healthState);
    m_attack = other.m_attack;
    return *this;
}

void BaseCharacter::TakeDamage(int damage)
{
    if (!IsAlive())
    {
        std::cout << GetName() << " уже побеждён\n";
        return;
    }
    if (damage <= 0)
    {
        std::cout << "Некорректный урон\n";
        return;
    }

    m_healthState->health = std::max(0, m_healthState->health - damage);
    std::cout << GetName() << " получает " << damage << " урона. HP: "
              << GetHealth() << "/" << GetMaxHealth() << '\n';
}

void BaseCharacter::RestoreHealth(int amount)
{
    if (IsAlive() && amount > 0)
    {
        m_healthState->health += std::min(amount,
            m_healthState->maxHealth - m_healthState->health);
    }
}

void BaseCharacter::ShareHealthWith(const BaseCharacter& other)
{
    m_healthState = other.m_healthState;
}

std::string BaseCharacter::GetBaseInfo() const
{
    return "Имя: " + m_name + ", HP: " + std::to_string(GetHealth())
        + "/" + std::to_string(GetMaxHealth())
        + ", атака: " + std::to_string(m_attack);
}

bool BaseCharacter::IsAlive() const
{
    return GetHealth() > 0;
}

std::string_view BaseCharacter::GetName() const
{
    return m_name;
}

int BaseCharacter::GetHealth() const
{
    return m_healthState ? m_healthState->health : 0;
}

int BaseCharacter::GetMaxHealth() const
{
    return m_healthState ? m_healthState->maxHealth : 0;
}

int BaseCharacter::GetAttack() const
{
    return m_attack;
}

int BaseCharacter::GetId() const
{
    return m_id;
}

int BaseCharacter::GetCreatedCount()
{
    return s_createdCount;
}

std::string BaseCharacter::Describe() const
{
    return "Персонаж №" + std::to_string(m_id) + ": " + GetBaseInfo();
}
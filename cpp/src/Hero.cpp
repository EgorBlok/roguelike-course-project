#include "Hero.hpp"

#include <iostream>

Hero::Hero(std::string_view name, int maxHealth, int attack)
    : BaseCharacter{ name.empty() ? std::string_view{ "Безымянный герой" } : name,
                     maxHealth, attack }
{
    std::cout << "[Hero] Конструктор: " << GetName() << '\n';
}

Hero::Hero(const Hero& other)
    : BaseCharacter{ other }
    , m_coins{ other.m_coins }
    , m_inventory{ other.m_inventory }
    , m_enemy{ other.m_enemy }
{
    std::cout << "[Hero] Копирование: " << GetName() << '\n';
}

Hero::~Hero()
{
    std::cout << "[Hero] Деструктор: " << GetName() << '\n';
}

Hero& Hero::operator=(const Hero& other)
{
    if (this == &other)
    {
        return *this;
    }

    BaseCharacter::operator=(other);
    m_coins = other.m_coins;
    m_inventory = other.m_inventory;
    m_enemy = other.m_enemy;
    return *this;
}

void Hero::Heal(int amount)
{
    if (!IsAlive() || amount <= 0 || GetHealth() == GetMaxHealth())
    {
        std::cout << "Лечение невозможно\n";
        return;
    }

    RestoreHealth(amount);
    std::cout << GetName() << " восстанавливает HP: " << GetHealth() << '\n';
}

void Hero::AttackEnemy()
{
    if (!IsAlive())
    {
        std::cout << "Погибший герой не может атаковать\n";
        return;
    }

    const std::shared_ptr<Enemy> enemy = m_enemy.lock();
    if (!enemy || !enemy->IsAlive())
    {
        std::cout << "Нет живого противника\n";
        return;
    }

    std::cout << GetName() << " атакует " << enemy->GetName() << '\n';
    enemy->TakeDamage(GetAttack());
}

void Hero::SetEnemy(const std::shared_ptr<Enemy>& enemy)
{
    m_enemy = enemy;
}

void Hero::AddCoins(int amount)
{
    if (amount > 0)
    {
        m_coins += amount;
    }
}

int Hero::GetCoins() const
{
    return m_coins;
}

Inventory& Hero::GetInventory()
{
    return m_inventory;
}

std::string_view Hero::GetRole() const
{
    return "Герой";
}

// Дополняет реализацию базового класса.
std::string Hero::Describe() const
{
    return BaseCharacter::Describe() + ", монеты: " + std::to_string(m_coins);
}

std::unique_ptr<BaseCharacter> Hero::Clone() const
{
    return std::make_unique<Hero>(*this);
}

void Hero::ShowInfo() const
{
    std::cout << Describe() << '\n';
    m_inventory.ShowInfo();
}
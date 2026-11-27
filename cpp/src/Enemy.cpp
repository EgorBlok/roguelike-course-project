#include "Enemy.hpp"

#include <iostream>

Enemy::Enemy(std::string_view name, int maxHealth, int attack)
    : BaseCharacter{ name.empty() ? std::string_view{ "Неизвестный противник" } : name,
                     maxHealth, attack }
{
    std::cout << "[Enemy] Создан противник: " << GetName() << '\n';
}

Enemy::~Enemy()
{
    std::cout << "[Enemy] Уничтожен противник: " << GetName() << '\n';
}

int Enemy::Attack() const
{
    if (!IsAlive())
    {
        std::cout << GetName() << " не может атаковать\n";
        return 0;
    }

    std::cout << GetName() << " атакует! Урон: " << GetAttack() << '\n';
    return GetAttack();
}

std::string_view Enemy::GetRole() const
{
    return "Противник";
}

void Enemy::ShowInfo() const
{
    std::cout << "\n--- " << GetRole() << " ---\n"
              << GetBaseInfo() << '\n'
              << "Состояние: " << (IsAlive() ? "жив" : "побеждён") << '\n';
}

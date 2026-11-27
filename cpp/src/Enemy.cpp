#include "Enemy.hpp"

#include <iostream>
#include <utility>

Enemy::Enemy()
    : Enemy{ "Безымянный противник", 30, 5 }
{
    std::cout << "[Enemy] Конструктор по умолчанию\n";
}

Enemy::Enemy(std::string_view name, int maxHealth, int attack)
    : BaseCharacter{ name, maxHealth, attack }
{
    std::cout << "[Enemy] Конструктор с параметрами: " << GetName() << '\n';
}

Enemy::Enemy(const Enemy& other)
    : BaseCharacter{ other }
{
    std::cout << "[Enemy] Конструктор копирования: " << GetName() << '\n';
}

Enemy::Enemy(Enemy&& other) noexcept
    : BaseCharacter{ std::move(other) }
{
    std::cout << "[Enemy] Конструктор перемещения: " << GetName() << '\n';
}

Enemy::~Enemy()
{
    std::cout << "[Enemy] Деструктор: " << GetName() << '\n';
}

Enemy& Enemy::operator=(const Enemy& other)
{
    if (this == &other)
    {
        return *this;
    }

    BaseCharacter::operator=(other);
    return *this;
}

Enemy& Enemy::operator=(Enemy&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    BaseCharacter::operator=(std::move(other));
    return *this;
}

int Enemy::Attack() const
{
    if (!IsAlive())
    {
        std::cout << GetName() << " не может атаковать\n";
        return 0;
    }

    std::cout << GetName() << " атакует. Урон: " << GetAttack() << '\n';
    return GetAttack();
}

// Демонстрация поверхностной копии: здоровье становится общим.
Enemy Enemy::ShallowCopy() const
{
    Enemy copy{ *this };
    copy.ShareHealthWith(*this);
    return copy;
}

std::string_view Enemy::GetRole() const
{
    return "Противник";
}

std::string Enemy::Describe() const
{
    return "Враг " + std::string{ GetName() } + ", HP: "
        + std::to_string(GetHealth()) + "/" + std::to_string(GetMaxHealth())
        + ", атака: " + std::to_string(GetAttack());
}

std::unique_ptr<BaseCharacter> Enemy::Clone() const
{
    return std::make_unique<Enemy>(*this);
}

void Enemy::ShowInfo() const
{
    std::cout << Describe() << '\n';
}
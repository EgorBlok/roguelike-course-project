
#pragma once

#include "Inventory.hpp"
#include "Enemy.hpp"

#include <string>
#include <string_view>

class Hero
{
private:
    std::string m_name{};

    int m_maxHealth{};
    int m_health{};
    int m_attack{};
    int m_coins{ 0 };

    Inventory m_inventory{};
    Enemy* m_enemy{ nullptr };

public:
    Hero(std::string_view name, int maxHealth, int attack);
    ~Hero();

    Hero(const Hero&) = delete;
    Hero& operator=(const Hero&) = delete;

    void TakeDamage(int damage);
    void Heal(int amount);
    void AttackEnemy();

    void SetEnemy(Enemy* enemy);
    void AddCoins(int amount);

    void ShowInfo() const;

    bool IsAlive() const;

    int GetHealth() const;
    int GetCoins() const;

    Inventory& GetInventory();
};

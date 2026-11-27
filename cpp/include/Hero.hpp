#pragma once

#include "BaseCharacter.hpp"
#include "Inventory.hpp"
#include "Enemy.hpp"

#include <memory>
#include <string_view>

class Hero : public BaseCharacter
{
private:
    int m_coins{ 0 };
    Inventory m_inventory{};
    std::weak_ptr<Enemy> m_enemy{};

public:
    Hero(std::string_view name, int maxHealth, int attack);
    ~Hero() override;

    Hero(const Hero&) = delete;
    Hero& operator=(const Hero&) = delete;

    void Heal(int amount);
    void AttackEnemy();
    void SetEnemy(const std::shared_ptr<Enemy>& enemy);
    void AddCoins(int amount);

    std::string_view GetRole() const override;
    void ShowInfo() const override;

    int GetCoins() const;
    Inventory& GetInventory();
};

#pragma once

#include "BaseCharacter.hpp"
#include "Enemy.hpp"
#include "Inventory.hpp"

#include <memory>
#include <string_view>

class Hero final : public BaseCharacter
{
private:
    int m_coins{ 0 };
    Inventory m_inventory{};
    std::weak_ptr<Enemy> m_enemy{};

public:
    Hero(std::string_view name, int maxHealth, int attack);
    Hero(const Hero& other);
    ~Hero() override;

    Hero& operator=(const Hero& other);
    Hero(Hero&& other) = delete;
    Hero& operator=(Hero&& other) = delete;

    void Heal(int amount);
    void AttackEnemy();
    void SetEnemy(const std::shared_ptr<Enemy>& enemy);
    void AddCoins(int amount);

    int GetCoins() const;
    Inventory& GetInventory();

    std::string_view GetRole() const override;
    std::string Describe() const override;
    std::unique_ptr<BaseCharacter> Clone() const override;
    void ShowInfo() const override;
};
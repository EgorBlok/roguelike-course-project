#pragma once

#include "BaseCharacter.hpp"

#include <string_view>

class Enemy : public BaseCharacter
{
public:
    Enemy(std::string_view name, int maxHealth, int attack);
    ~Enemy() override;

    int Attack() const;
    std::string_view GetRole() const override;
    void ShowInfo() const override;
};

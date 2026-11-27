#pragma once

#include "BaseCharacter.hpp"

#include <memory>
#include <string_view>

class Enemy : public BaseCharacter
{
public:
    Enemy();
    Enemy(std::string_view name, int maxHealth, int attack);
    Enemy(const Enemy& other);
    Enemy(Enemy&& other) noexcept;
    ~Enemy() override;

    Enemy& operator=(const Enemy& other);
    Enemy& operator=(Enemy&& other) noexcept;

    int Attack() const;
    Enemy ShallowCopy() const;

    std::string_view GetRole() const override;
    std::string Describe() const override;
    std::unique_ptr<BaseCharacter> Clone() const override;
    void ShowInfo() const override;
};

#pragma once

#include <string>
#include <string_view>

class Enemy
{
private:
    std::string m_name{};
    int m_maxHealth{};
    int m_health{};
    int m_attack{};

public:
    Enemy(std::string_view name, int maxHealth, int attack);
    ~Enemy();

    void TakeDamage(int damage);
    int Attack() const;
    bool IsAlive() const;

    void ShowInfo() const;

    std::string_view GetName() const;
    int GetHealth() const;
    int GetMaxHealth() const;
};

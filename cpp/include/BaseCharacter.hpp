#pragma once

#include <string>
#include <string_view>

// Общие свойства любого участника боя.
class BaseCharacter
{
private:
    std::string m_name{};
    int m_maxHealth{};
    int m_health{};
    int m_attack{};

protected:
    // Доступен Hero и Enemy, но не вызывающему коду.
    std::string GetBaseInfo() const;
    void RestoreHealth(int amount);

public:
    BaseCharacter(std::string_view name, int maxHealth, int attack);
    virtual ~BaseCharacter();

    void TakeDamage(int damage);
    bool IsAlive() const;

    std::string_view GetName() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetAttack() const;

    // У каждого наследника собственная роль и своё описание.
    virtual std::string_view GetRole() const = 0;
    virtual void ShowInfo() const = 0;
};

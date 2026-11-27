#pragma once

#include <memory>
#include <string>
#include <string_view>

class BaseCharacter
{
private:
    struct HealthState
    {
        int maxHealth{};
        int health{};
    };

    inline static int s_createdCount{ 0 };

    int m_id{};
    std::string m_name{};
    std::shared_ptr<HealthState> m_healthState{};
    int m_attack{};

    static int NextId();

protected:
    void RestoreHealth(int amount);
    void ShareHealthWith(const BaseCharacter& other);
    std::string GetBaseInfo() const;

public:
    BaseCharacter(std::string_view name, int maxHealth, int attack);
    BaseCharacter(const BaseCharacter& other);
    BaseCharacter(BaseCharacter&& other) noexcept;
    virtual ~BaseCharacter();

    BaseCharacter& operator=(const BaseCharacter& other);
    BaseCharacter& operator=(BaseCharacter&& other) noexcept;

    void TakeDamage(int damage);
    bool IsAlive() const;

    std::string_view GetName() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetAttack() const;
    int GetId() const;

    static int GetCreatedCount();

    virtual std::string_view GetRole() const = 0;
    virtual std::string Describe() const;
    virtual std::unique_ptr<BaseCharacter> Clone() const = 0;
    virtual void ShowInfo() const = 0;
};
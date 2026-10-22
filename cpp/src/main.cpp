
#include "Hero.hpp"

#include <windows.h>
#include <iostream>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "=== Проверка класса Hero ===\n";

    // Противник существует независимо от героя
    Enemy enemy("Скелет", 50, 10);

    {
        // Создание героя автоматически создаёт инвентарь
        Hero hero("Воин", 100, 15);

        hero.ShowInfo();

        std::cout << "\n=== Проверка инвентаря ===\n";

        hero.GetInventory().AddItem("Зелье здоровья");
        hero.GetInventory().AddItem("Зелье силы");
        hero.GetInventory().EquipTalisman("Лекарь");

        hero.ShowInfo();

        std::cout << "\n=== Проверка агрегации ===\n";

        hero.SetEnemy(&enemy);

        std::cout << "\n=== Проверка боя ===\n";

        hero.AttackEnemy();
        hero.TakeDamage(enemy.Attack());

        hero.AttackEnemy();
        hero.TakeDamage(enemy.Attack());

        hero.AttackEnemy();
        hero.TakeDamage(enemy.Attack());

        hero.AttackEnemy();

        std::cout << "\n=== Проверка лечения ===\n";

        hero.Heal(20);

        std::cout << "\n=== Проверка монет ===\n";

        hero.AddCoins(10);
        hero.AddCoins(-5);

        hero.ShowInfo();

        std::cout << "\n=== Конец области видимости героя ===\n";
    }

    // Герой и его инвентарь уже уничтожены.
    // Противник продолжает существовать.
    std::cout << "\n=== Противник после уничтожения героя ===\n";

    enemy.ShowInfo();

    return 0;
}

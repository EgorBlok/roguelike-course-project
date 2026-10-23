
#include "Hero.hpp"

#include <windows.h>
#include <iostream>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "=== Лабораторная работа №3 ===\n";

    // =====================================
    // 1. Композиция и агрегация
    // =====================================

    std::cout << "\n=== 1. Композиция и агрегация ===\n";

    Enemy enemy("Скелет", 50, 10);

    {
        Hero hero("Воин", 100, 15);

        hero.GetInventory().AddItem("Зелье здоровья");
        hero.GetInventory().AddItem("Зелье силы");
        hero.GetInventory().EquipTalisman("Лекарь");

        hero.SetEnemy(&enemy);

        hero.ShowInfo();

        // Проверка боя
        std::cout << "\n--- Бой ---\n";

        hero.AttackEnemy();
        hero.TakeDamage(enemy.Attack());

        hero.AttackEnemy();
        hero.TakeDamage(enemy.Attack());

        hero.AttackEnemy();
        hero.TakeDamage(enemy.Attack());

        hero.AttackEnemy();

        // Проверка лечения
        std::cout << "\n--- Лечение ---\n";

        hero.Heal(20);

        // Проверка монет
        std::cout << "\n--- Монеты ---\n";

        hero.AddCoins(15);
        hero.AddCoins(-10);

        // Проверка инвентаря
        std::cout << "\n--- Проверка ограничений ---\n";

        hero.GetInventory().AddItem("Предмет 3");
        hero.GetInventory().AddItem("Предмет 4");
        hero.GetInventory().AddItem("Предмет 5");

        // Шестой предмет не должен добавиться
        hero.GetInventory().AddItem("Предмет 6");

        hero.ShowInfo();

        std::cout << "\n--- Завершение жизни героя ---\n";
    }

    // Герой и инвентарь уничтожены,
    // но противник продолжает существовать

    std::cout << "\n--- Противник после уничтожения героя ---\n";
    enemy.ShowInfo();

    // =====================================
    // 2. Статический объект
    // =====================================

    std::cout << "\n=== 2. Статический объект ===\n";

    static Enemy staticEnemy("Страж", 80, 12);

    staticEnemy.ShowInfo();

    // =====================================
    // 3. Динамический объект
    // =====================================

    std::cout << "\n=== 3. Динамический объект ===\n";

    Hero* dynamicHero = new Hero("Маг", 70, 20);

    dynamicHero->ShowInfo();

    delete dynamicHero;
    dynamicHero = nullptr;

    std::cout << "Динамический герой удалён\n";

    // =====================================
    // 4. Обычный массив объектов
    // =====================================

    std::cout << "\n=== 4. Обычный массив объектов ===\n";

    {
        Enemy enemies[3]{
            Enemy("Крыса", 20, 5),
            Enemy("Паук", 30, 7),
            Enemy("Гоблин", 40, 9)
        };

        for (int i = 0; i < 3; ++i)
        {
            enemies[i].ShowInfo();
        }

        std::cout << "Конец области видимости массива\n";
    }

    // =====================================
    // 5. Динамический массив объектов
    // =====================================

    std::cout << "\n=== 5. Динамический массив объектов ===\n";

    Inventory* inventories = new Inventory[3];

    for (int i = 0; i < 3; ++i)
    {
        inventories[i].AddItem("Зелье здоровья");
        inventories[i].ShowInfo();
    }

    delete[] inventories;
    inventories = nullptr;

    std::cout << "Динамический массив удалён\n";

    // =====================================
    // 6. Массив динамических объектов
    // =====================================

    std::cout << "\n=== 6. Массив динамических объектов ===\n";

    Enemy** enemyPointers = new Enemy*[3];

    enemyPointers[0] = new Enemy("Призрак", 35, 8);
    enemyPointers[1] = new Enemy("Орк", 70, 14);
    enemyPointers[2] = new Enemy("Демон", 100, 20);

    for (int i = 0; i < 3; ++i)
    {
        enemyPointers[i]->ShowInfo();
    }

    for (int i = 0; i < 3; ++i)
    {
        delete enemyPointers[i];
    }

    delete[] enemyPointers;
    enemyPointers = nullptr;

    std::cout << "Массив указателей удалён\n";

    std::cout << "\n=== Завершение программы ===\n";

    return 0;
}

#include "Hero.hpp"

#include <array>
#include <iostream>
#include <memory>
#include <utility>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "=== Лабораторная работа №3: умные указатели ===\n";

    // 1. Композиция: Inventory - поле Hero по значению.
    // Агрегация: Hero хранит weak_ptr, владение Enemy остаётся у main.
    std::cout << "\n=== 1. Композиция и агрегация ===\n";
    auto enemy = std::make_shared<Enemy>("Скелет", 50, 10);

    {
        Hero hero("Воин", 100, 15);
        hero.GetInventory().AddItem("Зелье здоровья");
        hero.GetInventory().AddItem("Зелье силы");
        hero.GetInventory().EquipTalisman("Лекарь");
        hero.SetEnemy(enemy);
        hero.ShowInfo();

        std::cout << "\n--- Бой ---\n";
        hero.AttackEnemy();
        hero.TakeDamage(enemy->Attack());
        hero.AttackEnemy();
        hero.TakeDamage(enemy->Attack());
        hero.AttackEnemy();
        hero.TakeDamage(enemy->Attack());
        hero.AttackEnemy();

        std::cout << "\n--- Лечение ---\n";
        hero.Heal(20);
        std::cout << "\n--- Монеты ---\n";
        hero.AddCoins(15);
        hero.AddCoins(-10);

        std::cout << "\n--- Проверка ограничений ---\n";
        hero.GetInventory().AddItem("Предмет 3");
        hero.GetInventory().AddItem("Предмет 4");
        hero.GetInventory().AddItem("Предмет 5");
        hero.GetInventory().AddItem("Предмет 6");
        hero.ShowInfo();
        std::cout << "\n--- Завершение жизни героя ---\n";
    } // Герой и его инвентарь уничтожаются, Enemy пока жив.

    std::cout << "\n--- Противник после уничтожения героя ---\n";
    enemy->ShowInfo();
    std::cout << "Владельцев противника после уничтожения героя: "
              << enemy.use_count() << '\n';

    // 2. Статический объект
    std::cout << "\n=== 2. Статический объект ===\n";
    static Enemy staticEnemy("Страж", 80, 12);
    staticEnemy.ShowInfo();

    // 3. unique_ptr: выход из блока и передача владения через std::move.
    std::cout << "\n=== 3. unique_ptr: динамический герой ===\n";
    {
        auto dynamicHero = std::make_unique<Hero>("Маг", 70, 20);
        dynamicHero->ShowInfo();

        auto newOwner = std::move(dynamicHero);
        std::cout << "После std::move исходный указатель пуст: "
                  << (dynamicHero == nullptr ? "да" : "нет") << '\n';
        std::cout << "Новый владелец управляет героем:\n";
        newOwner->ShowInfo();
        std::cout << "Выход из блока unique_ptr\n";
    } // Вызываются ~Hero и ~Inventory, без delete.

    // 4. Обычный массив
    std::cout << "\n=== 4. Обычный массив объектов ===\n";
    {
        Enemy enemies[3]{
            Enemy("Крыса", 20, 5),
            Enemy("Паук", 30, 7),
            Enemy("Гоблин", 40, 9)
        };
        for (const Enemy& current : enemies)
        {
            current.ShowInfo();
        }
        std::cout << "Конец области видимости массива\n";
    }

    // 5. unique_ptr<T[]>: замена new Inventory[3] / delete[].
    std::cout << "\n=== 5. Динамический массив объектов ===\n";
    {
        auto inventories = std::make_unique<Inventory[]>(3);
        for (int i = 0; i < 3; ++i)
        {
            inventories[i].AddItem("Зелье здоровья");
            inventories[i].ShowInfo();
        }
        std::cout << "Выход из блока динамического массива\n";
    }

    // 6. Массив отдельных умных указателей на динамические объекты.
    std::cout << "\n=== 6. Массив динамических объектов ===\n";
    {
        std::array<std::unique_ptr<Enemy>, 3> enemyPointers{};
        enemyPointers[0] = std::make_unique<Enemy>("Призрак", 35, 8);
        enemyPointers[1] = std::make_unique<Enemy>("Орк", 70, 14);
        enemyPointers[2] = std::make_unique<Enemy>("Демон", 100, 20);

        for (const auto& current : enemyPointers)
        {
            current->ShowInfo();
        }
        std::cout << "Выход из блока массива unique_ptr\n";
    }

    // 7. shared_ptr: копирование увеличивает счётчик владельцев.
    std::cout << "\n=== 7. shared_ptr: несколько владельцев ===\n";
    {
        auto sharedEnemy = std::make_shared<Enemy>("Двойник", 45, 11);
        std::cout << "Владельцев после создания: " << sharedEnemy.use_count() << '\n';
        {
            auto secondOwner = sharedEnemy;
            std::cout << "Владельцев после копирования: " << sharedEnemy.use_count() << '\n';
            secondOwner->ShowInfo();
        }
        std::cout << "Владельцев после выхода из внутреннего блока: "
                  << sharedEnemy.use_count() << '\n';
        std::cout << "Выход последнего владельца\n";
    } // Здесь уничтожается Двойник.

    // 8. weak_ptr: наблюдатель не удерживает объект в памяти.
    std::cout << "\n=== 8. weak_ptr: проверка существования противника ===\n";
    {
        Hero observer("Наблюдатель", 40, 8);
        auto temporaryEnemy = std::make_shared<Enemy>("Временный враг", 20, 3);
        observer.SetEnemy(temporaryEnemy);
        std::weak_ptr<Enemy> watcher = temporaryEnemy;

        if (auto locked = watcher.lock())
        {
            std::cout << "До удаления владельца: " << locked->GetName() << " существует\n";
        }

        temporaryEnemy.reset(); // Последний shared_ptr исчез, объект уничтожен.
        std::cout << "После reset() слабая ссылка истекла: "
                  << (watcher.expired() ? "да" : "нет") << '\n';
        if (auto locked = watcher.lock())
        {
            locked->ShowInfo();
        }
        else
        {
            std::cout << "lock() вернул пустой shared_ptr\n";
        }
        observer.AttackEnemy(); // Безопасная обработка исчезнувшего объекта.
    }

    std::cout << "\n=== Завершение программы ===\n";
    return 0;
}

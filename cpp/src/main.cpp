#include "BaseCharacter.hpp"
#include "Enemy.hpp"
#include "Hero.hpp"

#include <array>
#include <iostream>
#include <memory>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "=== Лабораторная работа №4: наследование ===\n";

    // Пункты 1–3: абстрактный класс и два наследника.
    // Пункт 12: работа с разными наследниками через базовый указатель.
    {
        std::array<std::unique_ptr<BaseCharacter>, 2> characters{
            std::make_unique<Hero>("Рыцарь", 100, 15),
            std::make_unique<Enemy>("Орк-страж", 60, 12)
        };

        for (const auto& character : characters)
        {
            std::cout << "\nТип персонажа: " << character->GetRole() << '\n';
            character->ShowInfo();
        }

        // Пункты 4–6: protected используется в ShowInfo(),
        // здесь также видны конструкторы и виртуальные деструкторы.
        std::cout << "\nОбъекты уничтожаются при выходе из блока.\n";
    }

    return 0;
}

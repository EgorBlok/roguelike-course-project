#include "BaseCharacter.hpp"
#include "Enemy.hpp"
#include "Hero.hpp"

#include <iostream>
#include <memory>
#include <string>
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

    // Пункты 1-4, 8, 12: абстрактный класс, наследники, protected,
    std::cout << "\n1. Наследование и полиморфизм\n";
    {
        std::unique_ptr<BaseCharacter> characters[] = {
            std::make_unique<Hero>("Рыцарь", 100, 15),
            std::make_unique<Enemy>("Орк", 50, 8)
        };

        for (const auto& character : characters)
        {
            std::cout << "Роль: " << character->GetRole() << '\n';
            character->ShowInfo();
        }
        // Пункт 6: объекты удаляются через указатель на BaseCharacter.
        std::cout << "Выход из блока (работа виртуальных деструкторов)\n";
    }

    // Пункт 5: конструкторы по умолчанию, с параметрами, копирования, перемещения.
    std::cout << "\n2. Разные конструкторы\n";
    {
        Enemy first;
        Enemy second("Скелет", 40, 6);
        Enemy copied(second);
        Enemy moved(std::move(copied));
        moved.ShowInfo();
    }

    // Пункт 7: поверхностная и глубокая копии, Clone(), присваивание.
    std::cout << "\n3. Копирование и клонирование\n";
    {
        Enemy original("Тень", 50, 9);

        Enemy shallow = original.ShallowCopy();
        shallow.TakeDamage(10);
        std::cout << "HP оригинала после изменения поверхностной копии: "
                  << original.GetHealth() << '\n'; 

        Enemy deep(original);
        deep.TakeDamage(15);
        std::cout << "HP оригинала после изменения глубокой копии: "
                  << original.GetHealth() << '\n';
        std::cout << "HP глубокой копии: " << deep.GetHealth() << '\n';

        std::unique_ptr<BaseCharacter> clone = original.Clone();
        clone->TakeDamage(5);
        std::cout << "HP оригинала после Clone(): "
                  << original.GetHealth() << '\n';

        deep = original;
        deep = deep; // Проверка this == &other: самоприсваивание.
        std::cout << "HP после присваивания: " << deep.GetHealth() << '\n';
    }

    // Пункты 9 и 11: строки и статический счётчик.
    std::cout << "\n4. Строки и static\n";
    std::string fullName = "Орк-страж элитный";
    const std::size_t space = fullName.find(' ');
    std::string shortName = fullName.substr(0, space);
    std::string label = "Противник: " + shortName;
    if (shortName == "Орк-страж")
    {
        std::cout << label << '\n';
    }
    std::cout << "Всего создано персонажей: "
              << BaseCharacter::GetCreatedCount() << '\n';

    return 0;
}
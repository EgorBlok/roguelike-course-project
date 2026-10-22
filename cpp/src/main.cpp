
#include "Enemy.hpp"

#include <windows.h>
#include <iostream>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "=== Проверка класса Enemy ===\n";

    Enemy enemy("Скелет", 50, 10);

    enemy.ShowInfo();

    std::cout << "\n--- Проверка получения урона ---\n";

    enemy.TakeDamage(20);
    enemy.TakeDamage(-10);

    enemy.ShowInfo();

    std::cout << "\n--- Проверка атаки ---\n";

    int damage = enemy.Attack();
    std::cout << "Полученный урон от атаки: "
              << damage << '\n';

    std::cout << "\n--- Проверка смерти ---\n";

    enemy.TakeDamage(100);

    enemy.ShowInfo();

    // Побеждённый противник не может атаковать
    enemy.Attack();

    // Нельзя повторно наносить урон побеждённому
    enemy.TakeDamage(10);

    return 0;
}

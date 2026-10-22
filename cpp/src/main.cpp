
#include "Inventory.hpp"

#include <iostream>
#include <windows.h>
#include <clocale>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Inventory inventory;

    // Добавляем пять предметов
    inventory.AddItem("Зелье здоровья");
    inventory.AddItem("Зелье силы");
    inventory.AddItem("Зелье здоровья");
    inventory.AddItem("Зелье защиты");
    inventory.AddItem("Зелье силы");

    // Проверяем ограничение вместимости
    inventory.AddItem("Шестой предмет");

    inventory.ShowInfo();

    // Удаляем один предмет
    inventory.RemoveItem("Зелье силы");

    // Экипируем и заменяем талисман
    inventory.EquipTalisman("Берсерк");
    inventory.EquipTalisman("Лекарь");

    inventory.ShowInfo();

    return 0;
}

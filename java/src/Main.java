import java.lang.ref.WeakReference;

public class Main {
    private static WeakReference<Enemy> createTemporaryEnemy() {
        Enemy temp = new Enemy("Временный призрак", 20, 5);
        return new WeakReference<>(temp);
    }

    public static void main(String[] args) {
        System.out.println("=== Лабораторная работа №3: Java ===");

        System.out.println("\n=== 1. Композиция и агрегация ===");
        Enemy enemy = new Enemy("Скелет", 50, 10);
        Hero hero = new Hero("Воин", 100, 15);
        hero.addItem("Зелье здоровья");
        hero.addItem("Зелье силы");
        hero.equipTalisman("Лекарь");
        hero.setEnemy(enemy);
        hero.showInfo();

        System.out.println("\n--- Бой ---");
        hero.attackEnemy();
        hero.takeDamage(enemy.attack());
        hero.attackEnemy();
        hero.takeDamage(enemy.attack());
        hero.attackEnemy();
        hero.takeDamage(enemy.attack());
        hero.attackEnemy();

        System.out.println("\n--- Лечение и монеты ---");
        hero.heal(20);
        hero.addCoins(15);
        hero.addCoins(-10);

        System.out.println("\n--- Ограничение инвентаря: максимум 5 ---");
        hero.addItem("Предмет 3");
        hero.addItem("Предмет 4");
        hero.addItem("Предмет 5");
        hero.addItem("Предмет 6");
        hero.showInfo();

        System.out.println("\n--- Агрегация: противник доступен отдельно от героя ---");
        hero.setEnemy(null);
        hero = null;
        enemy.showInfo();

        System.out.println("\n=== 2. Ссылки вместо копирования объекта ===");
        Hero first = new Hero("Лучник", 80, 12);
        Hero second = first;
        second.takeDamage(25);
        System.out.println("Здоровье через first: " + first.getHealth());
        System.out.println("first == second: " + (first == second));

        System.out.println("\n=== 3. Освобождение ресурса ===");
        try (GameLog log = new GameLog("Подземелье")) {
            log.write("Бой завершён");
        }
        System.out.println("Код после блока try: ресурс уже закрыт");

        System.out.println("\n=== 4. Сборщик мусора ===");
        WeakReference<Enemy> watcher = createTemporaryEnemy();
        System.out.println("Слабая ссылка до запроса GC: " + (watcher.get() != null));
        System.gc();
        System.out.println("Слабая ссылка после запроса GC: " + (watcher.get() != null));

        System.out.println("\n=== Завершение программы ===");
    }
}

public class Hero {
    private final String name;
    private final int maxHealth;
    private int health;
    private final int attack;
    private int coins;

    private final Inventory inventory; // Композиция: создаётся самим героем, наружу не выдаётся
    private Enemy enemy;                // Агрегация: противник создан снаружи

    public Hero(String name, int maxHealth, int attack) {
        this.name = name == null || name.isEmpty() ? "Безымянный герой" : name;
        this.maxHealth = Math.max(1, maxHealth);
        this.health = this.maxHealth;
        this.attack = Math.max(1, attack);
        this.inventory = new Inventory();
        System.out.println("[Hero] Герой создан: " + this.name);
    }

    public void takeDamage(int damage) {
        if (!isAlive()) {
            System.out.println(name + " уже побеждён");
            return;
        }
        if (damage <= 0) {
            System.out.println("Некорректный урон");
            return;
        }
        health = Math.max(0, health - damage);
        System.out.println(name + " получает " + damage + " урона. Здоровье: " + health + "/" + maxHealth);
        if (!isAlive()) {
            System.out.println(name + " погиб!");
        }
    }

    public void heal(int amount) {
        if (!isAlive()) {
            System.out.println("Нельзя лечить погибшего героя");
            return;
        }
        if (amount <= 0 || health == maxHealth) {
            System.out.println("Лечение невозможно");
            return;
        }
        health += Math.min(amount, maxHealth - health);
        System.out.println(name + " восстанавливает здоровье: " + health + "/" + maxHealth);
    }

    public void attackEnemy() {
        if (!isAlive()) {
            System.out.println("Погибший герой не может атаковать");
            return;
        }
        if (enemy == null) {
            System.out.println("Нет текущего противника");
            return;
        }
        if (!enemy.isAlive()) {
            System.out.println("Противник уже побеждён");
            return;
        }
        System.out.println(name + " атакует " + enemy.getName());
        enemy.takeDamage(attack);
    }

    public void setEnemy(Enemy enemy) {
        this.enemy = enemy;
        System.out.println(enemy == null ? "Текущий противник отсутствует"
                : "Текущий противник: " + enemy.getName());
    }

    public void addCoins(int amount) {
        if (amount <= 0) {
            System.out.println("Некорректное количество монет");
            return;
        }
        coins += amount;
        System.out.println("Получено монет: " + amount + ". Всего: " + coins);
    }

    public boolean addItem(String name) { return inventory.addItem(name); }
    public boolean removeItem(String name) { return inventory.removeItem(name); }
    public boolean equipTalisman(String name) { return inventory.equipTalisman(name); }
    public int getItemsCount() { return inventory.getItemsCount(); }
    public String getTalisman() { return inventory.getTalisman(); }

    public boolean isAlive() { return health > 0; }
    public int getHealth() { return health; }
    public int getCoins() { return coins; }

    public void showInfo() {
        System.out.println("\n--- Герой ---");
        System.out.println(toString());
        inventory.showInfo();
    }

    @Override
    public String toString() {
        return "Имя: " + name + "\nЗдоровье: " + health + "/" + maxHealth
                + "\nАтака: " + attack + "\nМонеты: " + coins;
    }
}

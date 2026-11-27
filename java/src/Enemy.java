public class Enemy {
    private final String name;
    private final int maxHealth;
    private int health;
    private final int attack;

    public Enemy(String name, int maxHealth, int attack) {
        this.name = name == null || name.isEmpty() ? "Неизвестный противник" : name;
        this.maxHealth = Math.max(1, maxHealth);
        this.health = this.maxHealth;
        this.attack = Math.max(1, attack);
        System.out.println("[Enemy] Создан противник: " + this.name);
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
            System.out.println(name + " побеждён!");
        }
    }

    public int attack() {
        if (!isAlive()) {
            System.out.println(name + " не может атаковать");
            return 0;
        }
        System.out.println(name + " атакует! Урон: " + attack);
        return attack;
    }

    public boolean isAlive() { return health > 0; }
    public String getName() { return name; }
    public int getHealth() { return health; }
    public int getMaxHealth() { return maxHealth; }

    public void showInfo() {
        System.out.println("\n--- Противник ---");
        System.out.println(toString());
    }

    @Override
    public String toString() {
        return "Имя: " + name + "\nЗдоровье: " + health + "/" + maxHealth
                + "\nАтака: " + attack + "\nСостояние: " + (isAlive() ? "жив" : "побеждён");
    }
}

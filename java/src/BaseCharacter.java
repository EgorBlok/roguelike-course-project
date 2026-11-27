public abstract class BaseCharacter {
    // Вложенный объект нужен для демонстрации двух способов копирования.
    private static class HealthState {
        private final int maxHealth;
        private int health;

        private HealthState(int maxHealth) {
            this.maxHealth = Math.max(1, maxHealth);
            this.health = this.maxHealth;
        }

        private HealthState(HealthState other) {
            this.maxHealth = other.maxHealth;
            this.health = other.health;
        }
    }

    private static int createdCount = 0;

    private final int id;
    private final String name;
    private final int attack;
    private HealthState healthState;

    protected BaseCharacter(String name, int maxHealth, int attack) {
        this.id = nextId();
        this.name = name == null || name.isEmpty() ? "Без имени" : name;
        this.attack = Math.max(1, attack);
        this.healthState = new HealthState(maxHealth);
        System.out.println("[BaseCharacter] Конструктор: " + this.name);
    }

    // Конструктор копирования: создаём отдельный HealthState.
    protected BaseCharacter(BaseCharacter other) {
        this.id = nextId();
        this.name = other.name;
        this.attack = other.attack;
        this.healthState = new HealthState(other.healthState);
        System.out.println("[BaseCharacter] Копирование: " + this.name);
    }

    private static int nextId() {
        return ++createdCount;
    }

    public static int getCreatedCount() {
        return createdCount;
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

        healthState.health = Math.max(0, healthState.health - damage);
        System.out.println(name + " получает " + damage + " урона. HP: "
                + getHealth() + "/" + getMaxHealth());
    }

    protected void restoreHealth(int amount) {
        if (isAlive() && amount > 0) {
            healthState.health = Math.min(healthState.maxHealth, healthState.health + amount);
        }
    }

    protected void shareHealthWith(BaseCharacter other) {
        this.healthState = other.healthState;
    }

    protected String getBaseInfo() {
        return "Имя: " + name + ", HP: " + getHealth()
                + "/" + getMaxHealth() + ", атака: " + attack;
    }

    public boolean isAlive() {
        return getHealth() > 0;
    }

    public final String getName() {
        return name;
    }

    public int getHealth() {
        return healthState.health;
    }

    public int getMaxHealth() {
        return healthState.maxHealth;
    }

    public int getAttack() {
        return attack;
    }

    public int getId() {
        return id;
    }

    public String describe() {
        return "Персонаж №" + id + ": " + getBaseInfo();
    }

    public abstract String getRole();
    public abstract BaseCharacter cloneCharacter();
    public abstract void showInfo();
}
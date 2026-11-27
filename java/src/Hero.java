public final class Hero extends BaseCharacter {
    private int coins;
    private final Inventory inventory;
    private Enemy enemy;

    public Hero(String name, int maxHealth, int attack) {
        super(name == null || name.isEmpty() ? "Безымянный герой" : name,
                maxHealth, attack);
        this.inventory = new Inventory();
        System.out.println("[Hero] Конструктор: " + getName());
    }

    // Копируем героя и инвентарь, но внешний противник остаётся общим.
    public Hero(Hero other) {
        super(other);
        this.coins = other.coins;
        this.inventory = new Inventory(other.inventory);
        this.enemy = other.enemy;
        System.out.println("[Hero] Конструктор копирования: " + getName());
    }

    public void heal(int amount) {
        if (!isAlive() || amount <= 0 || getHealth() == getMaxHealth()) {
            System.out.println("Лечение невозможно");
            return;
        }
        restoreHealth(amount);
        System.out.println(getName() + " восстанавливает HP: " + getHealth());
    }

    public void attackEnemy() {
        if (!isAlive()) {
            System.out.println("Погибший герой не может атаковать");
            return;
        }
        if (enemy == null || !enemy.isAlive()) {
            System.out.println("Нет живого противника");
            return;
        }
        System.out.println(getName() + " атакует " + enemy.getName());
        enemy.takeDamage(getAttack());
    }

    public void setEnemy(Enemy enemy) {
        this.enemy = enemy;
    }

    public void addCoins(int amount) {
        if (amount > 0) {
            coins += amount;
        }
    }

    public boolean addItem(String name) {
        return inventory.addItem(name);
    }

    public boolean removeItem(String name) {
        return inventory.removeItem(name);
    }

    public boolean equipTalisman(String name) {
        return inventory.equipTalisman(name);
    }

    public int getItemsCount() {
        return inventory.getItemsCount();
    }

    public String getTalisman() {
        return inventory.getTalisman();
    }

    public int getCoins() {
        return coins;
    }

    @Override
    public String getRole() {
        return "Герой";
    }

    // Используем готовую реализацию базового класса и дополняем её.
    @Override
    public String describe() {
        return super.describe() + ", монеты: " + coins;
    }

    @Override
    public Hero cloneCharacter() {
        return new Hero(this);
    }

    @Override
    public void showInfo() {
        System.out.println(describe());
        inventory.showInfo();
    }
}
import java.util.Objects;

public class Enemy extends BaseCharacter {
    public Enemy() {
        this("Безымянный противник", 30, 5);
        System.out.println("[Enemy] Конструктор по умолчанию");
    }

    public Enemy(String name, int maxHealth, int attack) {
        super(name == null || name.isEmpty() ? "Неизвестный противник" : name,
                maxHealth, attack);
        System.out.println("[Enemy] Конструктор с параметрами");
    }

    // Глубокое копирование через конструктор базового класса.
    public Enemy(Enemy other) {
        super(other);
        System.out.println("[Enemy] Конструктор копирования");
    }

    public Enemy shallowCopy() {
        Enemy copy = new Enemy(this);
        copy.shareHealthWith(this);
        return copy;
    }

    public int attack() {
        if (!isAlive()) {
            System.out.println(getName() + " не может атаковать");
            return 0;
        }
        System.out.println(getName() + " атакует. Урон: " + getAttack());
        return getAttack();
    }

    @Override
    public String getRole() {
        return "Противник";
    }

    // В отличие от Hero, полностью заменяет метод базового класса.
    @Override
    public String describe() {
        return "Враг " + getName() + ", HP: " + getHealth()
                + "/" + getMaxHealth() + ", атака: " + getAttack();
    }

    @Override
    public Enemy cloneCharacter() {
        return new Enemy(this);
    }

    @Override
    public void showInfo() {
        System.out.println(describe());
    }

    // Равными считаем противников одного вида с одинаковыми исходными параметрами.
    // Текущее HP в сравнение не входит: оно меняется во время боя.
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Enemy other = (Enemy) obj;
        return getMaxHealth() == other.getMaxHealth()
                && getAttack() == other.getAttack()
                && getName().equals(other.getName());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getName(), getMaxHealth(), getAttack());
    }
}
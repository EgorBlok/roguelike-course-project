public class Main {
    public static void main(String[] args) {
        System.out.println("=== Лабораторная работа №4: наследование (Java) ===");

        // 1. Абстрактный класс, наследники, полиморфизм, protected, override и final.
        System.out.println("\n1. Наследование и полиморфизм");
        BaseCharacter[] characters = {
            new Hero("Рыцарь", 100, 15),
            new Enemy("Орк", 50, 8)
        };
        for (BaseCharacter character : characters) {
            System.out.println("Роль: " + character.getRole());
            character.showInfo();
        }

        // 2. Конструкторы по умолчанию, с параметрами и копирования.
        System.out.println("\n2. Конструкторы");
        Enemy first = new Enemy();
        Enemy second = new Enemy("Скелет", 40, 6);
        Enemy copied = new Enemy(second);
        copied.showInfo();

        // 3. Поверхностное и глубокое копирование, клонирование.
        System.out.println("\n3. Копирование и клонирование");
        Enemy original = new Enemy("Тень", 50, 9);
        Enemy shallow = original.shallowCopy();
        shallow.takeDamage(10);
        System.out.println("HP оригинала после поверхностной копии: "
                + original.getHealth()); 

        Enemy deep = new Enemy(original);
        deep.takeDamage(15);
        System.out.println("HP оригинала после глубокой копии: "
                + original.getHealth()); 
        System.out.println("HP глубокой копии: " + deep.getHealth());

        BaseCharacter clone = original.cloneCharacter();
        clone.takeDamage(5);
        System.out.println("HP оригинала после cloneCharacter(): "
                + original.getHealth()); 

        Hero hero = new Hero("Маг", 70, 12);
        hero.addItem("Зелье");
        Hero heroCopy = new Hero(hero);
        heroCopy.addItem("Эликсир");
        System.out.println("Предметов у оригинала: " + hero.getItemsCount());
        System.out.println("Предметов у копии: " + heroCopy.getItemsCount());   

        // 4. Сравнение объектов по содержимому: equals и hashCode.
        System.out.println("\n4. Сравнение объектов");
        Enemy a = new Enemy("Гоблин", 30, 5);
        Enemy b = new Enemy("Гоблин", 30, 5);
        System.out.println("a == b: " + (a == b)); 
        System.out.println("a.equals(b): " + a.equals(b)); 
        System.out.println("Хеш-коды совпадают: " + (a.hashCode() == b.hashCode()));

        // 5. Статическое поле и метод, this в конструкторах и equals.
        System.out.println("\n5. Статические члены");
        System.out.println("Всего создано персонажей: "
                + BaseCharacter.getCreatedCount());
    }
}
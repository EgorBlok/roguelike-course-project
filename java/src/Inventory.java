public class Inventory {
    private static final int MAX_ITEMS = 5;
    private final String[] items = new String[MAX_ITEMS];
    private int itemsCount;
    private String talisman = "";

    public Inventory() { this(0); }

    public Inventory(int initialItemsCount) {
        if (initialItemsCount >= 0 && initialItemsCount <= MAX_ITEMS) {
            itemsCount = initialItemsCount;
            for (int i = 0; i < itemsCount; i++) {
                items[i] = "Начальный предмет";
            }
        }
        System.out.println("[Inventory] Инвентарь создан");
    }

    public boolean addItem(String itemName) {
        if (itemName == null || itemName.isEmpty() || itemsCount >= MAX_ITEMS) {
            System.out.println("Нельзя добавить предмет");
            return false;
        }
        items[itemsCount++] = itemName;
        System.out.println("Добавлен предмет: " + itemName);
        return true;
    }

    public boolean removeItem(String itemName) {
        for (int i = 0; i < itemsCount; i++) {
            if (items[i].equals(itemName)) {
                for (int j = i; j < itemsCount - 1; j++) {
                    items[j] = items[j + 1];
                }
                items[--itemsCount] = null;
                System.out.println("Удалён предмет: " + itemName);
                return true;
            }
        }
        System.out.println("Предмет не найден");
        return false;
    }

    public boolean equipTalisman(String talismanName) {
        if (talismanName == null || talismanName.isEmpty()) {
            System.out.println("Некорректное название талисмана");
            return false;
        }
        if (!talisman.isEmpty()) {
            System.out.println("Замена талисмана: " + talisman + " -> " + talismanName);
        }
        talisman = talismanName;
        System.out.println("Активный талисман: " + talisman);
        return true;
    }

    public int getItemsCount() { return itemsCount; }
    public String getTalisman() { return talisman; }

    public void showInfo() {
        System.out.println("\n--- Инвентарь ---");
        System.out.println(toString());
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder("Предметы: " + itemsCount + "/" + MAX_ITEMS);
        for (int i = 0; i < itemsCount; i++) {
            result.append("\n").append(i + 1).append(". ").append(items[i]);
        }
        result.append("\nТалисман: ").append(talisman.isEmpty() ? "отсутствует" : talisman);
        return result.toString();
    }
}

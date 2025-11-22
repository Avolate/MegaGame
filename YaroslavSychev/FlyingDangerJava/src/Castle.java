public class Castle {
    private int health;
    private int maxHealth;
    private String position;
    private String sprite;
    private String rect;

    // Константы
    public static final int DEFAULT_HEALTH = 100;
    public static final int DEFAULT_MAX_HEALTH = 100;
    public static final int CASTLE_ATTACK_DAMAGE = 10;

    public Castle() {
        this.health = DEFAULT_HEALTH;
        this.maxHealth = DEFAULT_MAX_HEALTH;
        this.position = "";
        this.sprite = "";
        this.rect = "";
        System.out.println("Объект класса Castle создан");
    }

    public Castle(int maxHealth) {
        this.health = maxHealth;
        this.maxHealth = maxHealth;
        this.position = "";
        this.sprite = "";
        this.rect = "";
        System.out.println("Объект класса Castle создан с максимальным здоровьем: " + maxHealth);
    }

    public void takeDamage(int amount) {
        if (amount < 0) {
            throw new IllegalArgumentException("Урон не может быть отрицательным: " + amount);
        }
        if (amount > 1000) {
            throw new IllegalStateException("Слишком большой урон: " + amount);
        }

        try {
            health -= amount;
            if (health < 0) {
                health = 0;
                throw new IllegalStateException("Замок разрушен!");
            }
            System.out.println("Метод takeDamage() класса Castle выполнен. Получено урона: " + amount);
            System.out.println("Осталось здоровья замка: " + health + "/" + maxHealth);
        } catch (IllegalStateException e) {
            System.out.println("КРИТИЧЕСКАЯ ОШИБКА: " + e.getMessage());
        }
    }

        public boolean isDestroyed() {
        boolean destroyed = health <= 0;
        System.out.println("Метод isDestroyed() класса Castle выполнен. Результат: " +
                (destroyed ? "разрушен" : "цел"));
        return destroyed;
    }

    public void draw() {
        System.out.println("Метод draw() класса Castle выполнен");
    }

    public int getHealth() { return health; }
    public int getMaxHealth() { return maxHealth; }
}
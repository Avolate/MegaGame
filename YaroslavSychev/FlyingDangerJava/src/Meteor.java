public class Meteor extends Enemy {
    private int size;
    private int damage;

    // Константы
    public static final int DEFAULT_SIZE = 3;
    public static final int DEFAULT_DAMAGE = 15;

    public Meteor() {
        super();
        this.size = DEFAULT_SIZE;
        this.damage = DEFAULT_DAMAGE;
        System.out.println("Объект класса Meteor создан");
    }

    public Meteor(int hp, int spd, int sz, int dmg) {
        super(hp, spd);
        this.size = sz;
        this.damage = dmg;
        System.out.println("Объект класса Meteor создан с параметрами");
    }

    public Meteor(int hp, int spd, int sz, int dmg, GameManager gm) {
        super(hp, spd, gm);
        this.size = sz;
        this.damage = dmg;
        System.out.println("Объект класса Meteor создан с ссылкой на GameManager");
    }

    public void move() {
        System.out.println("Метод move() класса Meteor выполнен");
        System.out.println("Метеор размера " + size + " движется со скоростью " + speed);
    }

    public void takeDamage(int amount) {
        health -= amount;
        System.out.println("Метод takeDamage() класса Meteor выполнен");
        System.out.println("Получено урона: " + amount + ", осталось здоровья: " + health);

        if (!isAlive()) {
            System.out.println("Метеор уничтожен!");
        }
    }

    public boolean checkCollision(String target) {
        System.out.println("Метод checkCollision() класса Meteor выполнен с целью: " + target);
        return true;
    }

    public void update() {
        System.out.println("Метод update() класса Meteor выполнен");

        move();
        checkBoundaries();
    }

    public void draw() {
        System.out.println("Метод draw() класса Meteor выполнен");
        System.out.println("Отрисовка метеора размера " + size + " в позиции " + position);
    }

    public void applyDamage(int amount) {
        System.out.println("Метод applyDamage() класса Meteor выполнен");
        takeDamage(amount);
    }

    public void checkBoundaries() {
        System.out.println("Метод checkBoundaries() класса Meteor выполнен");
        System.out.println("Проверка границ экрана для метеора в позиции " + position);

        if (position.contains("out")) {
            System.out.println("Метеор вышел за границы экрана!");
        }
    }

    public int getSize() { return size; }
    public int getDamage() { return damage; }
}
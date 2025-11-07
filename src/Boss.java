public class Boss extends Enemy {
    private int phase;
    private int size;
    private int damage;

    // Константы
    public static final int DEFAULT_PHASE = 1;
    public static final int DEFAULT_SIZE = 10;
    public static final int DEFAULT_DAMAGE = 30;
    public static final double PHASE_CHANGE_THRESHOLD = 0.5;
    public static final int PHASE_SPEED_BONUS = 2;
    public static final int PHASE_DAMAGE_BONUS = 10;

    public Boss() {
        super();
        this.phase = DEFAULT_PHASE;
        this.size = DEFAULT_SIZE;
        this.damage = DEFAULT_DAMAGE;
        System.out.println("Объект класса Boss создан");
    }

    public Boss(int hp, int spd, int ph, int sz, int dmg) {
        super(hp, spd);
        this.phase = ph;
        this.size = sz;
        this.damage = dmg;
        System.out.println("Объект класса Boss создан с параметрами");
    }

    public Boss(int hp, int spd, int ph, int sz, int dmg, GameManager gm) {
        super(hp, spd, gm);
        this.phase = ph;
        this.size = sz;
        this.damage = dmg;
        System.out.println("Объект класса Boss создан с ссылкой на GameManager");
    }

    public void move() {
        System.out.println("Метод move() класса Boss выполнен");
        System.out.println("Босс фазы " + phase + " движется к цели");
    }

    public void takeDamage(int amount) {
        health -= amount;
        System.out.println("Метод takeDamage() класса Boss выполнен");
        System.out.println("Получено урона: " + amount + ", осталось здоровья: " + health);

        if (health < maxHealth * PHASE_CHANGE_THRESHOLD && phase == 1) {
            changePhase();
        }

        if (!isAlive()) {
            System.out.println("Босс побежден!");
        }
    }

    public boolean checkCollision(String target) {
        System.out.println("Метод checkCollision() класса Boss выполнен с целью: " + target);
        return true;
    }

    public void update() {
        System.out.println("Метод update() класса Boss выполнен");

        move();

        if (phase > 1) {
            System.out.println("Босс использует специальную атаку фазы " + phase);
        }
    }

    public void draw() {
        System.out.println("Метод draw() класса Boss выполнен");
        System.out.println("Отрисовка босса размера " + size + " в фазе " + phase);
    }

    public void applyDamage(int amount) {
        System.out.println("Метод applyDamage() класса Boss выполнен");
        takeDamage(amount);
    }

    public void changePhase() {
        phase++;
        System.out.println("Босс перешел в фазу " + phase + "!");
        System.out.println("Скорость и урон увеличены!");

        speed += PHASE_SPEED_BONUS;
        damage += PHASE_DAMAGE_BONUS;
    }

    public int getPhase() { return phase; }
    public int getSize() { return size; }
    public int getDamage() { return damage; }
}
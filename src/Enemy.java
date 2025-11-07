public abstract class Enemy {
    protected int health;
    protected int maxHealth;
    protected int speed;
    protected String position;
    protected String sprite;
    protected String rect;
    protected GameManager gameManager;

    // Константы
    public static final int DEFAULT_HEALTH = 50;
    public static final int DEFAULT_MAX_HEALTH = 50;
    public static final int DEFAULT_SPEED = 2;
    public static final int CASTLE_ATTACK_DAMAGE = 10;

    public Enemy() {
        this.health = DEFAULT_HEALTH;
        this.maxHealth = DEFAULT_MAX_HEALTH;
        this.speed = DEFAULT_SPEED;
        this.position = "";
        this.sprite = "";
        this.rect = "";
        this.gameManager = null;
        System.out.println("Объект класса Enemy создан");
    }

    public Enemy(int hp, int spd) {
        this();
        this.health = hp;
        this.maxHealth = hp;
        this.speed = spd;
        System.out.println("Объект класса Enemy создан с параметрами");
    }

    public Enemy(int hp, int spd, GameManager gm) {
        this(hp, spd);
        this.gameManager = gm;
        System.out.println("Объект класса Enemy создан с ссылкой на GameManager");
    }

    public abstract void move();
    public abstract void takeDamage(int amount);
    public abstract boolean checkCollision(String target);
    public abstract void update();
    public abstract void draw();

    public void attackCastle(Castle castle) {
        if (castle != null && isAlive()) {
            System.out.println("Враг атакует замок!");
            castle.takeDamage(CASTLE_ATTACK_DAMAGE);
        }
    }

    public boolean isAlive() {
        return health > 0;
    }

    public void checkBoundaries() {
        System.out.println("Базовый метод checkBoundaries() класса Enemy");
    }

    public int getMaxHealth() { return maxHealth; }
}
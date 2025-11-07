public class Projectile {
    private String position;
    private String direction;
    private int speed;
    private int damage;
    private String rect;
    private boolean isActive;
    private Player owner;

    // Константы
    public static final int DEFAULT_SPEED = 10;
    public static final int DEFAULT_DAMAGE = 10;

    public Projectile() {
        this.position = "";
        this.direction = "";
        this.speed = DEFAULT_SPEED;
        this.damage = DEFAULT_DAMAGE;
        this.rect = "";
        this.isActive = true;
        this.owner = null;
        System.out.println("Объект класса Projectile создан");
    }

    public Projectile(String pos, String dir, int dmg) {
        this();
        this.position = pos;
        this.direction = dir;
        this.damage = dmg;
        System.out.println("Объект класса Projectile создан с параметрами");
    }

    public Projectile(String pos, String dir, int dmg, Player player) {
        this(pos, dir, dmg);
        this.owner = player;
        System.out.println("Объект класса Projectile создан с владельцем");
    }

    public void update() {
        System.out.println("Метод update() класса Projectile выполнен");
    }

    public boolean checkCollision(Enemy enemy) {
        System.out.println("Метод checkCollision() класса Projectile выполнен");
        return false;
    }

    public void onHit() {
        System.out.println("Метод onHit() класса Projectile выполнен");
        isActive = false;
    }

    public void checkBoundaries() {
        System.out.println("Метод checkBoundaries() класса Projectile выполнен");
    }

    public void draw() {
        System.out.println("Метод draw() класса Projectile выполнен");
    }

    public boolean isActive() { return isActive; }
    public int getDamage() { return damage; }
}
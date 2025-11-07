import java.util.ArrayList;
import java.util.List;

public class Player {
    private String position;
    private String sprite;
    private String rect;
    private int speed;
    private boolean isAlive;
    private float shootCooldown;
    private List<Projectile> projectiles;
    private GameManager gameManager;

    // Константы
    public static final int DEFAULT_SPEED = 5;
    public static final float DEFAULT_SHOOT_COOLDOWN = 0.5f;
    public static final int PROJECTILE_DAMAGE = 10;

    public Player() {
        this.position = "";
        this.sprite = "";
        this.rect = "";
        this.speed = DEFAULT_SPEED;
        this.isAlive = true;
        this.shootCooldown = DEFAULT_SHOOT_COOLDOWN;
        this.projectiles = new ArrayList<>();
        this.gameManager = null;
        System.out.println("Объект класса Player создан");
    }

    public Player(GameManager gm) {
        this();
        this.gameManager = gm;
        System.out.println("Объект класса Player создан с ссылкой на GameManager");
    }

    public void move(String mousePos) {
        System.out.println("Метод move() класса Player выполнен. Позиция мыши: " + mousePos);
    }

    public void shoot() {
        System.out.println("Метод shoot() класса Player выполнен");

        Projectile newProjectile = new Projectile(position, "forward", PROJECTILE_DAMAGE, this);
        addProjectile(newProjectile);
    }

    public void takeDamage() {
        System.out.println("Метод takeDamage() класса Player выполнен");
        isAlive = false;
    }

    public void update() {
        System.out.println("Метод update() класса Player выполнен");

        for (Projectile projectile : projectiles) {
            projectile.update();
        }
    }

    public void draw() {
        System.out.println("Метод draw() класса Player выполнен");
    }

    public void addProjectile(Projectile projectile) {
        projectiles.add(projectile);
        System.out.println("Снаряд добавлен игроку");
    }

    public void removeProjectile(Projectile projectile) {
        projectiles.remove(projectile);
        System.out.println("Снаряд удален у игрока");
    }
}
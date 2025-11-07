import java.util.ArrayList;
import java.util.List;

public class GameManager {
    private String screen;
    private String clock;
    private String gameState;
    private int score;
    private int castleHealth;
    private Castle castle;
    private Player player;
    private List<Enemy> enemies;

    // Константы
    public static final String DEFAULT_GAME_STATE = "menu";
    public static final int DEFAULT_SCORE = 0;
    public static final int DEFAULT_CASTLE_HEALTH = 100;

    public GameManager() {
        this.screen = "";
        this.clock = "";
        this.gameState = DEFAULT_GAME_STATE;
        this.score = DEFAULT_SCORE;
        this.castleHealth = DEFAULT_CASTLE_HEALTH;
        this.enemies = new ArrayList<>();

        this.castle = new Castle(DEFAULT_CASTLE_HEALTH);
        this.player = new Player();

        System.out.println("Объект класса GameManager создан");
    }

    public void run() {
        System.out.println("Метод run() класса GameManager запущен");
    }

    public void switchState() {
        System.out.println("Метод switchState() класса GameManager выполнен");
    }

    public void checkWinConditions() {
        System.out.println("Метод checkWinConditions() класса GameManager выполнен");
    }

    public void handleEvents() {
        System.out.println("Метод handleEvents() класса GameManager выполнен");
    }

    public void update() {
        System.out.println("Метод update() класса GameManager выполнен");
        System.out.println("Обновление состояния всех игровых объектов...");
    }

    public void addEnemy(Enemy enemy) {
        enemies.add(enemy);
        System.out.println("Враг добавлен в GameManager");
    }

    public void removeEnemy(Enemy enemy) {
        enemies.remove(enemy);
        System.out.println("Враг удален из GameManager");
    }
}
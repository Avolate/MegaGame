public class GameMain {
    private int health;
    private String background;
    private String gamestatus;
    
    public static final int FLOOR_Y = 5;
    public static final int MAX_FLOOR_Y = 20;
    public static final int MAX_FLOOR_X = 40;
    public static final int MAX_SPEED = 5;
    public static final int PLAYER_SIZE = 10;
    public static final int COUNT_CHANGE = 1;
    
    public GameMain(int h, String bg, String status) {
        this.health = h;
        this.background = bg;
        this.gamestatus = status;
        System.out.println("Объект GameMain создан");
    }
    
    public void start() {
        gamestatus = "playing";
        System.out.println("Метод start запущен. Game started!");
    }
    
    public void changeStatus() {
        if (gamestatus.equals("playing")) {
            gamestatus = "paused";
            System.out.println("Game paused.");
        } else {
            gamestatus = "playing";
            System.out.println("Game resumed.");
        }
    }
    
    public boolean winCheck(int countCandy, int countCake, int countDonut) {
        if (health > 0 && (countCandy == 0 && countCake == 0 && countDonut == 0)) {
            System.out.println("Игрок победил!");
            return true;
        } else {
            return false;
        }
    }
    
    public boolean loseCheck() {
        if (health <= 0) {
            System.out.println("Проверка проигрыша: Игрок проиграл!");
            return true;
        } else {
            System.out.println("Проверка проигрыша: Игрок еще жив");
            return false;
        }
    }
    
    public void displayInfo() {
        System.out.println("GameMain: Health=" + health + ", Background=" + background + ", Status=" + gamestatus);
    }
    
    // Getters and Setters
    public int getHealth() { return health; }
    public void setHealth(int health) { this.health = health; }
    public String getBackground() { return background; }
    public String getGamestatus() { return gamestatus; }
}
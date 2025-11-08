public class Player extends GameObject {
    private int speed;
    private boolean life;
    
    public Player(int x, int y, String spritePath, int spd, boolean alive) {
        super(x, y, spritePath);
        this.speed = spd;
        this.life = alive;
        System.out.println("Объект Player создан");
    }
    
    public void moveRight() {
        int newPosition = getPositionX();
        newPosition += speed;
        setPositionX(newPosition);
        System.out.println("Player перемещен вправо. Новая позиция X: " + getPositionX());
    }
    
    public void moveLeft() {
        int newPosition = getPositionX();
        newPosition -= speed;
        setPositionX(newPosition);
        System.out.println("Player перемещен влево. Новая позиция X: " + getPositionX());
    }
    
    // Getter and Setter
    public boolean getLife() { return life; }
    public void setLife(boolean life) { this.life = life; }
}
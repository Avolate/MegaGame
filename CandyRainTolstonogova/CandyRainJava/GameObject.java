public class GameObject {
    private int positionX;
    private int positionY;
    private String sprite;
    
    public GameObject(int x, int y, String spritePath) {
        this.positionX = x;
        this.positionY = y;
        this.sprite = spritePath;
        System.out.println("Объект GameObject создан");
    }
    
    // Getters
    public int getPositionX() { return positionX; }
    public int getPositionY() { return positionY; }
    public String getSprite() { return sprite; }
    
    // Setters
    public void setPositionX(int count) { this.positionX = count; }
    public void setPositionY(int count) { this.positionY = count; }
    public void setSprite(String bg) { this.sprite = bg; }
    
    public void displayInfo() {
        System.out.println("GameObject: X=" + positionX + ", Y=" + positionY + ", Sprite=" + sprite);
    }
}
public class FallingObject extends GameObject {
    private int speed;
    private int numb;
    private boolean playerTouch;
    private boolean floorTouch;
    
    public FallingObject(int x, int y, String spritePath, int spd, int num, boolean pTouch, boolean fTouch) {
        super(x, y, spritePath);
        this.speed = spd;
        this.numb = num;
        this.playerTouch = pTouch;
        this.floorTouch = fTouch;
        System.out.println("Объект FallingObject создан");
    }
    
    public void falling() {
        int newPosition = getPositionY();
        newPosition -= speed;
        setPositionY(newPosition);
        System.out.println(getSprite() + " падает. Новая позиция Y: " + getPositionY());
    }
    
    public void minusHealth(GameMain game) {
        if (game.getHealth() > 0) {
            game.setHealth(game.getHealth() - 1);
            System.out.println("Здоровье уменьшено. Текущее здоровье: " + game.getHealth());
        }
    }
    
    @Override
    public void displayInfo() {
        System.out.println("FallingObject: X=" + getPositionX() + ", Y=" + getPositionY() + 
                          ", Speed=" + speed + ", Number=" + numb);
    }
    
    // Getters and Setters
    public int getNumb() { return numb; }
    public boolean getPlayerTouch() { return playerTouch; }
    public boolean getFloorTouch() { return floorTouch; }
    public void setNumb(int count) { this.numb = count; }
    public void setPlayerTouch(boolean count) { this.playerTouch = count; }
    public void setFloorTouch(boolean count) { this.floorTouch = count; }
}
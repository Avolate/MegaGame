public class Character extends GameObject {
    private boolean isAlive;
    private int speedCharacter;
    private boolean isHanged;

    public Character() {
        super(); // Вызываем конструктор базового класса
        this.isAlive = true;
        this.speedCharacter = 5;
        this.isHanged = false;

        // Устанавливаем позицию и спрайт через сеттеры
        setPositionX(10);
        setPositionY(10);
        setSprite("player_sprite.png");

        System.out.println("--- Character Initialized ---");
        System.out.println("  Position: (" + getPositionX() + ", " + getPositionY() + ")");
        System.out.println("  Sprite: '" + getSprite() + "'");
        System.out.println("  Is Alive: " + isAlive);
        System.out.println("  Speed: " + speedCharacter);
        System.out.println("  Is Hanged: " + isHanged);
    }

    @Override
    protected void finalize() throws Throwable {
        System.out.println("--- Character Destroyed ---");
        System.out.println("  Final Position: (" + getPositionX() + ", " + getPositionY() + ")");
        System.out.println("  Final State: Alive = " + isAlive);
        super.finalize();
    }

    public void movementRight() {
        System.out.println("Character.movementRight() called. Current X: " + getPositionX());
        setPositionX(getPositionX() + getSpeedCharacter());
        System.out.println("Character.movementRight(): Moved Right. New position X: " + getPositionX());
    }

    public void movementLeft() {
        System.out.println("Character.movementLeft() called. Current X: " + getPositionX());
        setPositionX(getPositionX() - getSpeedCharacter());
        System.out.println("Character.movementLeft(): Moved Left. New position X: " + getPositionX());
    }

    public void jump() {
        System.out.println("Character.jump() called. Performing jump.");
        // Логика прыжка
    }

    public void fallingCharacter() {
        System.out.println("Character.fallingCharacter() called. Current Y: " + getPositionY());
        setPositionY(getPositionY() - 1); // Имитация падения
        System.out.println("Character.fallingCharacter(): Falling. New position Y: " + getPositionY());
    }

    // Getters
    public boolean getIsAlive() { return isAlive; }
    public int getSpeedCharacter() { return speedCharacter; }
    public boolean getIsHanged() { return isHanged; }

    // Setters
    public void setIsAlive(boolean alive) {
        this.isAlive = alive;
        System.out.println("Character.setIsAlive() called. New state: isAlive = " + isAlive);
    }
    public void setSpeedCharacter(int speed) {
        this.speedCharacter = speed;
        System.out.println("Character.setSpeedCharacter() called. New speed: " + speedCharacter);
    }
    public void setIsHanged(boolean hanged) {
        this.isHanged = hanged;
        System.out.println("Character.setIsHanged() called. New state: isHanged = " + isHanged);
    }
}
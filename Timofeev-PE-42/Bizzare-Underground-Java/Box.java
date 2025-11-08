public class Box { // Не наследуется от GameObject в этом примере
    private boolean isHanged;
    private int speedFalling;
    private int speedMovement;

    public Box() {
        this.isHanged = false;
        this.speedFalling = 2;
        this.speedMovement = 3;
        System.out.println("--- Box Initialized ---");
        System.out.println("  Is Hanged: " + isHanged);
        System.out.println("  Speed Falling: " + speedFalling);
        System.out.println("  Speed Movement: " + speedMovement);
    }

    @Override
    protected void finalize() throws Throwable {
        System.out.println("--- Box Destroyed ---");
        super.finalize();
    }

    public void checkHanged() {
        System.out.println("Box.checkHanged() called. Checking if box is hanging.");
        // Логика проверки
    }

    public void fallingBox() {
        System.out.println("Box.fallingBox() called. Simulating fall.");
        System.out.println("Box.fallingBox(): Box is falling. (Requires positionY)");
    }

    public void movementBox() {
        System.out.println("Box.movementBox() called. Simulating movement.");
    }

    public boolean characterBoxContact(int characterPositionX, int characterPositionY) {
        System.out.println("Box.characterBoxContact() called. Checking Character(" + characterPositionX + ", " + characterPositionY + ") against Box.");
        return false;
    }

    // Getters
    public boolean getIsHanged() { return isHanged; }
    public int getSpeedFalling() { return speedFalling; }
    public int getSpeedMovement() { return speedMovement; }

    // Setters
    public void setIsHanged(boolean hanged) { this.isHanged = hanged; }
    public void setSpeedFalling(int sf) { this.speedFalling = sf; }
    public void setSpeedMovement(int sm) { this.speedMovement = sm; }
}
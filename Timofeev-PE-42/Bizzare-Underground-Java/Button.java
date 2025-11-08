public class Button { // Не наследуется от GameObject в этом примере
    private boolean isPressed;
    private int cooldownButton;

    public Button() {
        this.isPressed = false;
        this.cooldownButton = 100;
        System.out.println("--- Button Initialized ---");
        System.out.println("  Cooldown: " + cooldownButton);
    }

    @Override
    protected void finalize() throws Throwable {
        System.out.println("--- Button Destroyed ---");
        super.finalize();
    }

    public boolean characterButtonContact(int characterPositionX, int characterPositionY) {
        System.out.println("Button.characterButtonContact() called. Character at (" + characterPositionX + ", " + characterPositionY + ") pressed button.");
        setIsPressed(true);
        return true;
    }

    public boolean boxButtonContact(int boxPositionX, int boxPositionY) {
        System.out.println("Button.boxButtonContact() called. Box at (" + boxPositionX + ", " + boxPositionY + ") pressed button.");
        setIsPressed(true);
        return true;
    }

    public boolean buttonChanges(boolean wallBlockIsHide, boolean spikeIsHide) {
        System.out.println("Button.buttonChanges() called. Applying changes.");
        System.out.println("  -> WallBlock hide status set to: " + wallBlockIsHide);
        System.out.println("  -> Spike hide status set to: " + spikeIsHide);
        // Логика изменения состояния других объектов
        return true;
    }

    // Getters
    public boolean getIsPressed() { return isPressed; }
    public int getCooldownButton() { return cooldownButton; }

    // Setters
    public void setIsPressed(boolean pressed) { this.isPressed = pressed; }
    public void setCooldownButton(int cooldown) { this.cooldownButton = cooldown; }
}
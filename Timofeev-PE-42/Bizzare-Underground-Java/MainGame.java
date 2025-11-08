public class MainGame {
    private String background;
    private int exitX;
    private int exitY;

    public MainGame() {
        this.background = "DefaultBG";
        this.exitX = 100;
        this.exitY = 100;
        System.out.println("--- MainGame Initialized ---");
        System.out.println("  Background: '" + getBackground() + "'");
        System.out.println("  Exit Position: (" + getExitX() + ", " + getExitY() + ")");
    }

    @Override
    protected void finalize() throws Throwable {
        System.out.println("--- MainGame Destroyed ---");
        super.finalize();
    }

    public void startGame(boolean isAlive) {
        System.out.println("MainGame.startGame() called. Player initial state: " + (isAlive ? "Alive" : "Dead"));
    }

    public boolean win(int characterPositionX, int characterPositionY) {
        System.out.println("MainGame.win() called. Checking condition at Character(" + characterPositionX + ", " + characterPositionY + ").");
        if (characterPositionX == getExitX() && characterPositionY == getExitY()) {
            System.out.println("MainGame.win(): VICTORY! Reached exit.");
            return true;
        }
        System.out.println("MainGame.win(): Not yet.");
        return false;
    }

    // Getters
    public String getBackground() { return background; }
    public int getExitX() { return exitX; }
    public int getExitY() { return exitY; }

    // Setters
    public void setBackground(String bg) {
        this.background = bg;
        System.out.println("MainGame.setBackground() called. New background: '" + this.background + "'");
    }
    public void setExitX(int x) {
        this.exitX = x;
        System.out.println("MainGame.setExitX() called. New exitX: " + this.exitX);
    }
    public void setExitY(int y) {
        this.exitY = y;
        System.out.println("MainGame.setExitY() called. New exitY: " + this.exitY);
    }
}
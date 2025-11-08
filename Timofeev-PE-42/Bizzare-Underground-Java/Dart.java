public class Dart { // Не наследуется от GameObject в этом примере
    private int speed;
    private int spawnSpeed;
    private boolean status;

    public Dart() {
        this.speed = 3;
        this.spawnSpeed = 50;
        this.status = true;
        System.out.println("--- Dart Initialized ---");
        System.out.println("  Speed: " + speed);
        System.out.println("  Spawn Speed: " + spawnSpeed);
        System.out.println("  Status: " + status);
    }

    @Override
    protected void finalize() throws Throwable {
        System.out.println("--- Dart Destroyed ---");
        System.out.println("  Final Status: " + status);
        super.finalize();
    }

    public boolean characterDartContact(int characterPositionX, int characterPositionY) {
        System.out.println("Dart.characterDartContact() called. Checking Character(" + characterPositionX + ", " + characterPositionY + ") against Dart.");
        return false;
    }

    public boolean dartWallContact(int wallBlockPositionX, int wallBlockPositionY) {
        System.out.println("Dart.dartWallContact() called. Checking WallBlock(" + wallBlockPositionX + ", " + wallBlockPositionY + ") against Dart.");
        return false;
    }

    public boolean dartBoxContact(int boxPositionX, int boxPositionY) {
        System.out.println("Dart.dartBoxContact() called. Checking Box(" + boxPositionX + ", " + boxPositionY + ") against Dart.");
        return false;
    }

    public void dartFlight() {
        System.out.println("Dart.dartFlight() called. Simulating flight.");
        // Логика полета
    }

    public void dartDestroy() {
        System.out.println("Dart.dartDestroy() called. Current status: " + status);
        setStatus(false);
        System.out.println("Dart.dartDestroy(): Dart destroyed. New status: " + status);
    }

    // Getters
    public int getSpeed() { return speed; }
    public int getSpawnSpeed() { return spawnSpeed; }
    public boolean getStatus() { return status; }

    // Setters
    public void setSpeed(int s) { this.speed = s; }
    public void setSpawnSpeed(int ss) { this.spawnSpeed = ss; }
    public void setStatus(boolean st) { this.status = st; }
}
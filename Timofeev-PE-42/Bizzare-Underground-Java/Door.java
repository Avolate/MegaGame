public class Door { // Не наследуется от GameObject в этом примере
    private int keyCounter;

    public Door() {
        this.keyCounter = 0;
        System.out.println("--- Door Initialized ---");
        System.out.println("  Required keys: 3");
    }

    @Override
    protected void finalize() throws Throwable {
        System.out.println("--- Door Destroyed ---");
        super.finalize();
    }

    public void doorOpen() {
        System.out.println("Door.doorOpen() called. Current key count: " + getKeyCounter());
        if (getKeyCounter() >= 3) {
            System.out.println("Door.doorOpen(): Opened successfully! Key count (" + getKeyCounter() + ") is sufficient.");
        } else {
            System.out.println("Door.doorOpen(): Blocked. Need " + (3 - getKeyCounter()) + " more keys.");
        }
    }

    // Getter
    public int getKeyCounter() { return keyCounter; }

    // Setter
    public void setKeyCounter(int count) {
        this.keyCounter = count;
        System.out.println("Door.setKeyCounter() called. New count: " + keyCounter);
    }
}
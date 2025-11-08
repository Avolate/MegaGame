public class Key { // Не наследуется от GameObject в этом примере
    public Key() {
        System.out.println("Key created on the map.");
    }

    @Override
    protected void finalize() throws Throwable {
        System.out.println("Key destroyed.");
        super.finalize();
    }

    public boolean characterKeyContact(int characterPositionX, int characterPositionY) {
        System.out.println("Key.characterKeyContact() called. Character at (" + characterPositionX + ", " + characterPositionY + ") found key.");
        return true; // Предполагаем контакт
    }

    public int keyDestroy(int keyCounter) {
        System.out.println("Key.keyDestroy() called. Current key count: " + keyCounter);
        int newCounter = keyCounter + 1;
        System.out.println("Key.keyDestroy(): Key picked up. New total keys: " + newCounter);
        return newCounter;
    }
}
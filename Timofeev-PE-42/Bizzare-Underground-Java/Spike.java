public class Spike extends GameObject { // Наследуется от GameObject
    private boolean isHide;

    public Spike() {
        super(); // Вызываем конструктор базового класса
        this.isHide = true;
        // Задаем позицию и спрайт через сеттеры
        setPositionX(5);
        setPositionY(5);
        setSprite("spike_sprite.png");

        System.out.println("--- Spike Initialized ---");
        System.out.println("  Position: (" + getPositionX() + ", " + getPositionY() + ")");
        System.out.println("  Sprite: '" + getSprite() + "'");
        System.out.println("  Initial state: isHide = " + isHide);
    }

    @Override
    protected void finalize() throws Throwable {
        System.out.println("--- Spike Destroyed ---");
        System.out.println("  Final state: isHide = " + isHide);
        super.finalize();
    }

    public boolean characterSpikeContact(int characterPositionX, int characterPositionY) {
        System.out.println("Spike.characterSpikeContact() called. Checking Character(" + characterPositionX + ", " + characterPositionY + ") against Spike at (" + getPositionX() + ", " + getPositionY() + ").");

        // Проверяем, активен ли шип (!isHide) и совпадает ли позиция персонажа с позицией шипа
        if (!isHide && characterPositionX == getPositionX() && characterPositionY == getPositionY()) {
            System.out.println("Spike.characterSpikeContact(): DEADLY CONTACT!");
            return true;
        }
        System.out.println("Spike.characterSpikeContact(): No contact.");
        return false;
    }

    public void putingSpike() {
        System.out.println("Spike.putingSpike() called. Current isHide: " + isHide);
        setIsHide(false); // Делаем шип активным
        System.out.println("Spike.putingSpike(): Spike extended (made active). New state: isHide = " + isHide);
    }

    // Getter
    public boolean getIsHide() { return isHide; }

    // Setter
    public void setIsHide(boolean hide) {
        this.isHide = hide;
        System.out.println("Spike.setIsHide() called. New state: isHide = " + isHide);
    }
}
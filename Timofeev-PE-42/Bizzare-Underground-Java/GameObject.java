public class GameObject {
    protected int positionX; // protected позволяет доступ производным классам
    protected int positionY;
    protected String sprite;

    public GameObject() {
        this.positionX = 0;
        this.positionY = 0;
        this.sprite = "";
        System.out.println("GameObject (Base) created.");
    }

    // Деструктор в Java - finalize(), но он не является надежным способом управления ресурсами.
    // Лучше использовать try-with-resources или паттерн Closeable, если есть ресурсы, которые нужно явно освобождать.
    // Для простых полей, сборщик мусора справится.
    @Override
    protected void finalize() throws Throwable {
        System.out.println("GameObject (Base) destroyed.");
        super.finalize();
    }

    // Getters
    public int getPositionX() { return positionX; }
    public int getPositionY() { return positionY; }
    public String getSprite() { return sprite; }

    // Setters
    public void setPositionX(int x) {
        System.out.println("GameObject: Setting positionX to " + x + ".");
        this.positionX = x;
    }
    public void setPositionY(int y) {
        System.out.println("GameObject: Setting positionY to " + y + ".");
        this.positionY = y;
    }
    public void setSprite(String s) {
        System.out.println("GameObject: Setting sprite to '" + s + "'.");
        this.sprite = s;
    }
}
public class WallBlock extends GameObject {
    private boolean isHide;

    public WallBlock() {
        super(); // Вызываем конструктор базового класса
        this.isHide = true; // По умолчанию блок скрыт
        System.out.println("WallBlock created. Initial state: isHide = " + isHide);
    }

    @Override
    protected void finalize() throws Throwable {
        System.out.println("WallBlock destroyed. Final state: isHide = " + isHide);
        super.finalize();
    }

    public void putingWall() {
        System.out.println("WallBlock.putingWall() called. Current isHide: " + isHide);
        setIsHide(false); // Блок становится осязаемым
        System.out.println("WallBlock.putingWall(): Block extended (made tangible). New state: isHide = " + isHide);
    }

    // Getter
    public boolean getIsHide() { return isHide; }

    // Setter
    public void setIsHide(boolean hide) {
        this.isHide = hide;
        System.out.println("WallBlock.setIsHide() called. New state: isHide = " + isHide);
    }
}
public class Sweet extends FallingObject {
    
    public Sweet(int x, int y, String sprite, int spd, int num, boolean pTouch, boolean fTouch) {
        super(x, y, sprite, spd, num, pTouch, fTouch);
        System.out.println("Объект Sweet создан");
    }
    
    public void playerCatchSweet(int playerX, int playerY) {
        if (Math.abs(getPositionX() - playerX) < GameMain.PLAYER_SIZE && 
            Math.abs(getPositionY() - playerY) < GameMain.PLAYER_SIZE) {
            setPlayerTouch(true);
            System.out.println("Sweet пойман игроком!");
        }
    }
    
    public void sweetTouchFloor() {
        if (getPositionY() <= GameMain.FLOOR_Y) {
            setFloorTouch(true);
            System.out.println("Sweet коснулся пола");
        }
    }
    
    public void changeCandy(SweetsDistribution distribution) {
        distribution.setCountCandy(distribution.getCountCandy() - GameMain.COUNT_CHANGE);
        System.out.println("Счетчик конфет уменьшен: " + distribution.getCountCandy());
    }
    
    public void changeCake(SweetsDistribution distribution) {
        distribution.setCountCake(distribution.getCountCake() - GameMain.COUNT_CHANGE);
        System.out.println("Счетчик тортов уменьшен: " + distribution.getCountCake());
    }
    
    public void changeDonut(SweetsDistribution distribution) {
        distribution.setCountDonut(distribution.getCountDonut() - GameMain.COUNT_CHANGE);
        System.out.println("Счетчик пончиков уменьшен: " + distribution.getCountDonut());
    }
}
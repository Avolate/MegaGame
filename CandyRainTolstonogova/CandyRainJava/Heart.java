public class Heart extends FallingObject {
    
    public Heart(int x, int y, String sprite, int spd, int num, boolean pTouch, boolean fTouch) {
        super(x, y, sprite, spd, num, pTouch, fTouch);
        System.out.println("Объект Heart создан");
    }
    
    public void playerCatchHeart(int playerX, int playerY) {
        if (Math.abs(getPositionX() - playerX) < GameMain.PLAYER_SIZE && 
            Math.abs(getPositionY() - playerY) < GameMain.PLAYER_SIZE) {
            setPlayerTouch(true);
            System.out.println("Heart пойман игроком!");
        }
    }
    
    public void plusHealth(GameMain game) {
        game.setHealth(game.getHealth() + 1);
        System.out.println("Здоровье увеличено. Текущее здоровье: " + game.getHealth());
    }
}
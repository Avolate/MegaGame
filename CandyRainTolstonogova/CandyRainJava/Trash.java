public class Trash extends FallingObject {
    
    public Trash(int x, int y, String spritePath, int spd, int num, boolean pTouch, boolean fTouch) {
        super(x, y, spritePath, spd, num, pTouch, fTouch);
        System.out.println("Объект Trash создан");
    }
    
    public void playerCatchTrash(int playerX, int playerY) {
        if (Math.abs(getPositionX() - playerX) < GameMain.PLAYER_SIZE && 
            Math.abs(getPositionY() - playerY) < GameMain.PLAYER_SIZE) {
            setPlayerTouch(true);
            System.out.println("Trash пойман игроком!");
        }
    }
}
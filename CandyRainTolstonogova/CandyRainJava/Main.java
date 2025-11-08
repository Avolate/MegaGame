public class Main{
public static void main(String[] args) {
        int health = 3;
        GameMain game = new GameMain(health, "back_ground.png", "paused");
        game.start();
        
        SweetsDistribution distribution = new SweetsDistribution();
        int candyCount = distribution.getCountCandy();
        int donutCount = distribution.getCountDonut();
        int cakeCount = distribution.getCountCake();
        int trashCount = distribution.getCountTrash();
        
        // Статическая инициализация
        Player sweetTooth = new Player(
            (int)(Math.random() * GameMain.MAX_FLOOR_X) + 1, 
            GameMain.FLOOR_Y, 
            "player.png", 2, true
        );
        sweetTooth.displayInfo();
        
        int candyNum = 1;
        int donutNum = 2;
        int cakeNum = 3;
        int trashNum = 4;
        int heartNum = 5;
        
        // Динамическая инициализация объектов
        Heart fallHeart = new Heart(
            (int)(Math.random() * GameMain.MAX_FLOOR_X) + 1,
            GameMain.MAX_FLOOR_Y,
            "heart.png",
            (int)(Math.random() * GameMain.MAX_SPEED) + 1,
            heartNum, false, false
        );
        fallHeart.displayInfo();
        fallHeart.plusHealth(game);
        
        final int SIZE = 3;
        
        // Динамический массив объектов
        Sweet[] sweets = new Sweet[SIZE];
        sweets[0] = new Sweet(
            (int)(Math.random() * GameMain.MAX_FLOOR_X) + 1,
            GameMain.MAX_FLOOR_Y,
            "candy.png",
            (int)(Math.random() * GameMain.MAX_SPEED) + 1,
            candyNum, false, false
        );
        sweets[1] = new Sweet(
            (int)(Math.random() * GameMain.MAX_FLOOR_X) + 1,
            GameMain.MAX_FLOOR_Y,
            "kake.png",
            (int)(Math.random() * GameMain.MAX_SPEED) + 1,
            donutNum, false, false
        );
        sweets[2] = new Sweet(
            (int)(Math.random() * GameMain.MAX_FLOOR_X) + 1,
            GameMain.MAX_FLOOR_Y,
            "donut.png",
            (int)(Math.random() * GameMain.MAX_SPEED) + 1,
            cakeNum, false, false
        );
        
        for (int i = 0; i < SIZE; i++) {
            sweets[i].displayInfo();
        }
        
        // Массив динамических объектов
        Trash[] arrTrash = new Trash[SIZE];
        for (int i = 0; i < SIZE; i++) {
            arrTrash[i] = new Trash(
                (int)(Math.random() * GameMain.MAX_FLOOR_X) + 1,
                GameMain.MAX_FLOOR_Y,
                "trash.png",
                (int)(Math.random() * GameMain.MAX_SPEED) + 1,
                trashNum, false, false
            );
            arrTrash[i].displayInfo();
        }
        
        sweetTooth.moveRight();
        
        int playerX = 30;
        int playerY = 5;
        
        for (int i = 0; i < SIZE; i++) {
            sweets[i].falling();
            sweets[i].playerCatchSweet(playerX, playerY);
            sweets[i].sweetTouchFloor();
            arrTrash[i].falling();
            arrTrash[i].playerCatchTrash(playerX, playerY);
        }
        
        sweets[2].changeCandy(distribution);
        sweets[1].minusHealth(game);
        
        game.winCheck(distribution.getCountCandy(), distribution.getCountCake(), distribution.getCountDonut());
        game.loseCheck();
        
        // В Java сборка мусора автоматическая, но можно явно обнулить ссылки
        sweets = null;
        arrTrash = null;
    }
}
import java.util.ArrayList;
import java.util.List;

public class Main {
    // Константы для демонстрации
    private static final int CASTLE_INITIAL_HEALTH = 200;
    private static final int METEOR1_HEALTH = 80;
    private static final int METEOR1_SPEED = 2;
    private static final int METEOR1_SIZE = 4;
    private static final int METEOR1_DAMAGE = 20;
    private static final int METEOR2_HEALTH = 70;
    private static final int METEOR2_SPEED = 3;
    private static final int METEOR2_SIZE = 3;
    private static final int METEOR2_DAMAGE = 15;
    private static final int BOSS_HEALTH = 300;
    private static final int BOSS_SPEED = 1;
    private static final int BOSS_PHASE = 1;
    private static final int BOSS_SIZE = 12;
    private static final int BOSS_DAMAGE = 40;
    private static final int PLAYER_POSITION_X = 100;
    private static final int PLAYER_POSITION_Y = 150;
    private static final int PROJECTILE1_POSITION_X = 50;
    private static final int PROJECTILE1_POSITION_Y = 50;
    private static final int PROJECTILE2_POSITION_X = 60;
    private static final int PROJECTILE2_POSITION_Y = 60;
    private static final int METEOR_DAMAGE_AMOUNT = 15;
    private static final int METEOR2_DAMAGE_AMOUNT = 20;
    private static final int CASTLE_DAMAGE_AMOUNT = 25;
    private static final int BOSS_DAMAGE_THRESHOLD = 200;
    private static final int DYNAMIC_METEORS_COUNT = 2;
    private static final int PROJECTILE_ARRAY_SIZE = 2;

    public static void main(String[] args) {
        System.out.println("ПРОГРАММНАЯ РЕАЛИЗАЦИЯ ИГРЫ 'FLYING DANGER' НА JAVA\n");
        System.out.println("ХРОНОЛОГИЧЕСКАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ ДЕЙСТВИЙ:");

        // 1. Создание основных объектов
        System.out.println("\n1. СОЗДАНИЕ ОСНОВНЫХ ОБЪЕКТОВ:");
        GameManager gameManager = new GameManager();

        // 2. Создание игровых объектов
        System.out.println("\n2. СОЗДАНИЕ ИГРОВЫХ ОБЪЕКТОВ:");
        Castle castle = new Castle(CASTLE_INITIAL_HEALTH);
        Player player = new Player(gameManager);

        // 3. Старт игры
        System.out.println("\n3. ЗАПУСК ИГРОВОГО ПРОЦЕССА:");
        gameManager.run();

        // 4. Создание врагов
        System.out.println("\n4. СОЗДАНИЕ ВРАГОВ:");
        Meteor meteor1 = new Meteor(METEOR1_HEALTH, METEOR1_SPEED, METEOR1_SIZE, METEOR1_DAMAGE, gameManager);
        Meteor meteor2 = new Meteor(METEOR2_HEALTH, METEOR2_SPEED, METEOR2_SIZE, METEOR2_DAMAGE, gameManager);
        Boss boss = new Boss(BOSS_HEALTH, BOSS_SPEED, BOSS_PHASE, BOSS_SIZE, BOSS_DAMAGE, gameManager);

        // 5. Добавление врагов в менеджер
        System.out.println("\n5. ДОБАВЛЕНИЕ ВРАГОВ В ИГРУ:");
        gameManager.addEnemy(meteor1);
        gameManager.addEnemy(meteor2);
        gameManager.addEnemy(boss);

        // 6. Действия игрока
        System.out.println("\n6. ДЕЙСТВИЯ ИГРОКА:");
        player.move(PLAYER_POSITION_X + "," + PLAYER_POSITION_Y);
        player.shoot();
        player.update();

        // 7. Движение врагов
        System.out.println("\n7. ДВИЖЕНИЕ ВРАГОВ:");
        meteor1.move();
        meteor2.move();
        boss.move();

        // 8. Создание снарядов
        System.out.println("\n8. СОЗДАНИЕ СНАРЯДОВ:");
        Projectile projectile1 = new Projectile(PROJECTILE1_POSITION_X + "," + PROJECTILE1_POSITION_Y, "1,0", 25, player);
        Projectile projectile2 = new Projectile(PROJECTILE2_POSITION_X + "," + PROJECTILE2_POSITION_Y, "1,1", 30, player);

        // 9. Обновление снарядов
        System.out.println("\n9. ОБНОВЛЕНИЕ СНАРЯДОВ:");
        projectile1.update();
        projectile2.update();

        // 10. Атаки и получение урона
        System.out.println("\n10. АТАКИ И ПОЛУЧЕНИЕ УРОНА:");
        meteor1.takeDamage(METEOR_DAMAGE_AMOUNT);
        meteor2.takeDamage(METEOR2_DAMAGE_AMOUNT);
        castle.takeDamage(CASTLE_DAMAGE_AMOUNT);

        // 11. Проверка столкновений
        System.out.println("\n11. ПРОВЕРКА СТОЛКНОВЕНИЙ:");
        projectile1.checkCollision(meteor1);
        meteor1.checkCollision("castle");

        // 12. Смена фазы босса
        System.out.println("\n12. СМЕНА ФАЗЫ БОССА:");
        boss.takeDamage(BOSS_DAMAGE_THRESHOLD);

        // 13. Демонстрация полиморфизма
        System.out.println("\n13. ПОЛИМОРФИЗМ:");
        List<Enemy> enemies = new ArrayList<>();
        enemies.add(meteor1);
        enemies.add(meteor2);
        enemies.add(boss);

        for (Enemy enemy : enemies) {
            enemy.update();
            enemy.draw();
        }

        // 14. Динамический массив объектов
        System.out.println("\n14. ДИНАМИЧЕСКИЙ МАССИВ ОБЪЕКТОВ:");
        Projectile[] projectileArray = new Projectile[PROJECTILE_ARRAY_SIZE];
        for (int i = 0; i < PROJECTILE_ARRAY_SIZE; i++) {
            projectileArray[i] = new Projectile();
            projectileArray[i].update();
        }

        // 15. Массив динамических объектов
        System.out.println("\n15. МАССИВ ДИНАМИЧЕСКИХ ОБЪЕКТОВ:");
        Meteor[] dynamicMeteors = new Meteor[DYNAMIC_METEORS_COUNT];
        for (int i = 0; i < DYNAMIC_METEORS_COUNT; i++) {
            dynamicMeteors[i] = new Meteor(50 + i * 10, 2, 3, 15, gameManager);
            dynamicMeteors[i].move();
        }

        System.out.println("\nКОНЕЦ ДЕМОНСТРАЦИИ!");

        System.out.println("Для выхода нажмите Enter...");
        try {
            System.in.read();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
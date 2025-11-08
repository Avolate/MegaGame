import java.util.ArrayList; // Для ArrayList (аналог std::vector)
import java.util.List;

public class Main {

    public static void main(String[] args) {
        System.out.println("--- Program Start ---");

        // Создание объектов. В Java объекты создаются через 'new'.
        // Сборка мусора (GC) будет управлять их уничтожением.
        // Мы можем вызывать finalize() для вывода сообщений, но не можем полагаться на него.
        MainGame game = new MainGame();
        Character player = new Character();
        WallBlock wall = new WallBlock();
        Spike spike = new Spike();
        Box box = new Box();
        Button button = new Button();
        Door door = new Door();

        // =================================================================
        // ДЕМОНСТРАЦИЯ: ДИНАМИЧЕСКИЙ МАССИВ (ArrayList) ОБЪЕКТОВ КЛАССА Key
        // =================================================================
        // В Java, ArrayList является распространенным способом создания динамических массивов.
        // Он хранит ссылки на объекты.
        List<Key> keyInventory = new ArrayList<>();
        final int totalKeys = 3;

        System.out.println("\n--- Creating " + totalKeys + " Keys (Dynamic Array - ArrayList) ---");
        for (int i = 0; i < totalKeys; ++i) {
            Key newKey = new Key();
            keyInventory.add(newKey); // Добавляем ссылку на новый ключ в список
        }

        System.out.println("--- Simulating Key Collection ---");
        
        int keysCollected = door.getKeyCounter(); // Начинаем с 0

        // Проходимся по списку ключей.
        // Так как ArrayList хранит ссылки, мы можем итерироваться напрямую.
        // Удаление из ArrayList во время итерации может быть сложным.
        // Безопаснее пройтись с конца или использовать итератор.
        
        // Удаляем и обрабатываем ключи, пока список не пуст
        while (!keyInventory.isEmpty()) {
            // Получаем ключ из конца списка
            Key currentKey = keyInventory.get(keyInventory.size() - 1);
            keyInventory.remove(keyInventory.size() - 1); // Удаляем из списка

            // Обработка ключа
            if (currentKey.characterKeyContact(player.getPositionX(), player.getPositionY())) {
                keysCollected = currentKey.keyDestroy(keysCollected);
            }
            
            // В Java нет ручного delete. JVM (сборщик мусора) позаботится об этом,
            // когда на объекты не останется ссылок.
            // Чтобы увидеть finalize(), нам нужно убедиться, что объект больше не используется.
            // Обычно это происходит, когда объект удаляется из ArrayList и на него нет других ссылок.
        }
        
        door.setKeyCounter(keysCollected);
        System.out.println("Total keys collected: " + door.getKeyCounter());
        // =================================================================
        // КОНЕЦ ДЕМОНСТРАЦИИ
        // =================================================================

        System.out.println("\n--- Game Flow Simulation ---");
        
        // 1. Character actions
        // Используем оператор "." для доступа к членам объектов
        player.movementRight();
        player.jump();
        player.fallingCharacter();

        // 2. World/Object interaction
        wall.putingWall();
        spike.putingSpike();

        // 3. Collision checks
        spike.characterSpikeContact(player.getPositionX(), player.getPositionY());
        box.characterBoxContact(player.getPositionX(), player.getPositionY());
        button.characterButtonContact(player.getPositionX(), player.getPositionY());

        // 4. Button logic
        if (button.getIsPressed()) {
            button.buttonChanges(wall.getIsHide(), spike.getIsHide());
        }

        // 5. Door check (после сбора ключей)
        door.doorOpen();

        // 6. Game loop simulation snippet
        game.win(player.getPositionX(), player.getPositionY());

        System.out.println("\n--- End of main method ---");
    }
}
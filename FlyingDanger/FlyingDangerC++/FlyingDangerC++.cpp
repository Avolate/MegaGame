#include <iostream>
#include <vector>
#include "GameManager.hpp"
#include "Castle.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Meteor.hpp"
#include "Boss.hpp"
using namespace std;

int main() {
    system("chcp 1251");
    cout << "ПРОГРАММНАЯ РЕАЛИЗАЦИЯ КЛАССОВ ИГРЫ 'FLYING DANGER'\n" << endl;
    cout << "ХРОНОЛОГИЧЕСКАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ ДЕЙСТВИЙ:" << endl;

    // 1. Создание основных объектов (композиция)
    cout << "\n1. СОЗДАНИЕ ОСНОВНЫХ ОБЪЕКТОВ:" << endl;
    GameManager* gameManager = new GameManager();

    // 2. Создание игровых объектов
    cout << "\n2. СОЗДАНИЕ ИГРОВЫХ ОБЪЕКТОВ:" << endl;
    Castle* castle = new Castle(200);
    Player* player = new Player(gameManager);

    // 3. Старт игры
    cout << "\n3. ЗАПУСК ИГРОВОГО ПРОЦЕССА:" << endl;
    gameManager->Run();

    // 4. Создание врагов
    cout << "\n4. СОЗДАНИЕ ВРАГОВ:" << endl;
    Meteor* meteor1 = new Meteor(80, 2, 4, 20, gameManager);
    Meteor* meteor2 = new Meteor(70, 3, 3, 15, gameManager);
    Boss* boss = new Boss(300, 1, 1, 12, 40, gameManager);

    // 5. Добавление врагов в менеджер
    cout << "\n5. ДОБАВЛЕНИЕ ВРАГОВ В ИГРУ:" << endl;
    gameManager->AddEnemy(meteor1);
    gameManager->AddEnemy(meteor2);
    gameManager->AddEnemy(boss);

    // 6. Действия игрока
    cout << "\n6. ДЕЙСТВИЯ ИГРОКА:" << endl;
    player->Move("100,150");
    player->Shoot();
    player->Update();

    // 7. Движение врагов
    cout << "\n7. ДВИЖЕНИЕ ВРАГОВ:" << endl;
    meteor1->Move();
    meteor2->Move();
    boss->Move();

    // 8. Создание снарядов
    cout << "\n8. СОЗДАНИЕ СНАРЯДОВ:" << endl;
    Projectile* projectile1 = new Projectile("50,50", "1,0", 25, player);
    Projectile* projectile2 = new Projectile("60,60", "1,1", 30, player);

    // 9. Обновление снарядов
    cout << "\n9. ОБНОВЛЕНИЕ СНАРЯДОВ:" << endl;
    projectile1->Update();
    projectile2->Update();

    // 10. Атаки и получение урона
    cout << "\n10. АТАКИ И ПОЛУЧЕНИЕ УРОНА:" << endl;
    meteor1->TakeDamage(15);
    meteor2->TakeDamage(20);
    castle->TakeDamage(25);

    // 11. Проверка столкновений
    cout << "\n11. ПРОВЕРКА СТОЛКНОВЕНИЙ:" << endl;
    projectile1->CheckCollision(meteor1);
    meteor1->CheckCollision("castle");

    // 12. Смена фазы босса
    cout << "\n12. СМЕНА ФАЗЫ БОССА:" << endl;
    boss->TakeDamage(200);

    // 13. Демонстрация полиморфизма
    cout << "\n13. ПОЛИМОРФИЗМ:" << endl;
    vector<Enemy*> enemies;
    enemies.push_back(meteor1);
    enemies.push_back(meteor2);
    enemies.push_back(boss);

    for (Enemy* enemy : enemies) {
        enemy->Update();
        enemy->Draw();
    }

    // 14. Динамический массив объектов
    cout << "\n14. ДИНАМИЧЕСКИЙ МАССИВ ОБЪЕКТОВ:" << endl;
    Projectile* projectileArray = new Projectile[2];
    for (int i = 0; i < 2; ++i) {
        projectileArray[i].Update();
    }

    // 15. Массив динамических объектов
    cout << "\n15. МАССИВ ДИНАМИЧЕСКИХ ОБЪЕКТОВ:" << endl;
    Meteor* dynamicMeteors[2];
    for (int i = 0; i < 2; ++i) {
        dynamicMeteors[i] = new Meteor(50 + i * 10, 2, 3, 15);
        dynamicMeteors[i]->Move();
    }

    // 16. Работа с указателями и ссылками
    cout << "\n16. РАБОТА С УКАЗАТЕЛЯМИ И ССЫЛКАМИ:" << endl;
    Meteor* meteorPtr = new Meteor(90, 2, 5, 25);
    Meteor& meteorRef = *meteorPtr;
    meteorRef.Update();
    meteorRef.Draw();

    // 17. Обновление состояния игры
    cout << "\n17. ОБНОВЛЕНИЕ СОСТОЯНИЯ ИГРЫ:" << endl;
    gameManager->Update();
    gameManager->CheckWinConditions();

    // 18. Отрисовка всех объектов
    cout << "\n18. ОТРИСОВКА ОБЪЕКТОВ:" << endl;
    castle->Draw();
    player->Draw();
    meteor1->Draw();
    boss->Draw();

    // 19. Уничтожение объектов (обратный порядок создания)
    cout << "\n19. УНИЧТОЖЕНИЕ ОБЪЕКТОВ:" << endl;

    // Очистка динамических массивов
    delete[] projectileArray;

    for (int i = 0; i < 2; ++i) {
        delete dynamicMeteors[i];
    }

    // Очистка отдельных объектов
    delete meteorPtr;
    delete projectile1;
    delete projectile2;

    // Очистка основных объектов (автоматически удалит связанные)
    delete gameManager;

    // Очистка оставшихся объектов
    delete castle;
    delete player;

    cout << "КОНЕЦ!" << endl;

    // Чтобы консоль не закрывалась сразу
    cout << "Для выхода нажмите любую клавишу\n";
    cin.get();

    return 0;
}
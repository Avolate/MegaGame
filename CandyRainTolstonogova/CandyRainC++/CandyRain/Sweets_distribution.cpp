#include <iostream> // For cout
#include <cstdlib>  // For rand()
#include <ctime>
#include "Sweets_distribution.h"


Sweets_distribution::Sweets_distribution() {};

int Sweets_distribution::count_trash = 0;
int Sweets_distribution::count_candy = 0;
int Sweets_distribution::count_cake = 0;
int Sweets_distribution::count_donut = 0;

int Sweets_distribution::countCandyChoice() {
    srand(time(nullptr));
    count_candy = rand() % fix_count+1;
    std::cout << "Количество конфет выбрано: " << count_candy << std::endl;
    return count_candy;
}

int Sweets_distribution::countCakeChoice() {
    count_cake = rand() % fix_count+1;
    std::cout << "Количество тортов выбрано: " << count_cake << std::endl;
    return count_cake;
}

int Sweets_distribution::countDonutChoice() {
    count_donut = rand() % fix_count + 1;
    std::cout << "Количество пончиков выбрано: " << count_donut << std::endl;
    return count_donut;
}
int Sweets_distribution::countTrashChoice() {
    count_trash = max_count - (count_candy + count_cake + count_donut);
    std::cout << "Количество мусора загружено: " << count_trash << std::endl;
    return count_trash;

}

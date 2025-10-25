#include <iostream> // For cout
#include <cstdlib>  // For rand()
#include <ctime>
#include "Sweets_distribution.h"


SweetsDistribution::SweetsDistribution() {};

int SweetsDistribution::counttrash = 0;
int SweetsDistribution::countcandy = 0;
int SweetsDistribution::countcake = 0;
int SweetsDistribution::countdonut = 0;

int SweetsDistribution::CountCandyChoice() {
    srand(time(nullptr));
    countcandy = rand() % fix_count+1;
    std::cout << "Количество конфет выбрано: " << countcandy << std::endl;
    return countcandy;
}

int SweetsDistribution::CountCakeChoice() {
    countcake = rand() % fix_count+1;
    std::cout << "Количество тортов выбрано: " << countcake << std::endl;
    return countcake;
}

int SweetsDistribution::CountDonutChoice() {
    countdonut = rand() % fix_count + 1;
    std::cout << "Количество пончиков выбрано: " << countdonut << std::endl;
    return countdonut;
}
int SweetsDistribution::CountTrashChoice() {
    counttrash = max_count - (countcandy + countcake + countdonut);
    std::cout << "Количество мусора загружено: " << counttrash << std::endl;
    return counttrash;

}

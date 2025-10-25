#pragma once
class Sweets_distribution
{
private:
   
   
    Sweets_distribution();
public:
    static const int fix_count = 9;
    static const int max_count = 30;
    static int count_candy;
    static int count_cake;
    static int count_donut;
    static int count_trash;
    static int countCakeChoice();
    static int countTrashChoice();
    static int countCandyChoice();
    static int countDonutChoice();
};


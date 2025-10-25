#pragma once
class SweetsDistribution
{
private:
   
   
    SweetsDistribution();
public:
    static const int fix_count = 9;
    static const int max_count = 30;
    static int countcandy;
    static int countcake;
    static int countdonut;
    static int counttrash;
    static int CountCakeChoice();
    static int CountTrashChoice();
    static int CountCandyChoice();
    static int CountDonutChoice();
};


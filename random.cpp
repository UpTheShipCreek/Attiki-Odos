#include <random>
#include <ctime>
#include "random.h"

bool coin_flip(){
    // srand(time(NULL));
    if(rand() % 2){
        return true;
    }
    else return false;
}

int random_number(int max){
    int r = (rand()%max)+1;
    return r;
}
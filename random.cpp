#include <random>
#include <ctime>
#include "random.h"

bool coin_flip(){
    srand(time(NULL));
    if(rand() % 2){
        return true;
    }
    else return false;
}
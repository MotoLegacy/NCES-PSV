#include <stdlib.h>
#include <time.h>

int random(int min, int max) {
    srand(time(NULL));

    return min + rand() % ((max + 1) - min);
}

int getScreenRes(bool worh) {
    int res;

    if (worh) res = 960;
    else res = 544;

    #ifdef PSP
    res *= 0.5;
    #endif

    return res;
}
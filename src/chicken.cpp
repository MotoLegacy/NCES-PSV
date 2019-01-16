#include "chicken.h"
#include <stdlib.h>
#include <time.h>

int random(int min, int max) {
    static bool first = true;

    if (first) {  
        srand(time(NULL));
        first = false;
    }

    return min + rand() % ((max + 1) - min);
}

void Chicken::spawnChicken() {
    int chickX = 100;
    int chickY = 62;
    int screenX = 960;
    int screenY = 544;

    #ifdef PSP
    chickX *= 0.5;
    chickY *= 0.5;
    screenX *= 0.5;
    screenY *= 0.5;
    #endif

    chicRect.x = random(0, screenX - chickX);
    chicRect.y = random(0, screenY - chickY);
}

Chicken::Chicken() {
    int chickX = 100;
    int chickY = 62;

    #ifdef PSP
    chickX *= 0.5;
    chickY *= 0.5;
    #endif

    chicRect.h = chickY;
    chicRect.w = chickX;
    Chicken::spawnChicken();
}

rect Chicken::getRect() {
    return chicRect;
}
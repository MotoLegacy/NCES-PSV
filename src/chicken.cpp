#include "chicken.h"
#include "celery.h"
#include "functions.h"

void Chicken::spawnChicken() {
    int chickX = 100;
    int chickY = 62;

    #ifdef PSP
    chickX *= 0.5;
    chickY *= 0.5;
    #endif

    chicRect.x = random(0, getScreenRes(true) - chickX);
    chicRect.y = random(0, getScreenRes(false) - chickY);
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
#ifndef _CHICKEN_CAGE_
#define _CHICKEN_CAGE_

#include "collisionHelper.h"

class Chicken {
private: 
    rect chicRect;
public: 
    Chicken();
    rect getRect();
    void spawnChicken();
    int chickenEaten;
};

#endif
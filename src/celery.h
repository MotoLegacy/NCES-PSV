#ifndef _CELERY_CAGE_
#define _CELERY_CAGE_

#include "collisionHelper.h"

class Celery {
private: 
    rect celRect;
    int celeryWidth;
    int celeryHeight;
public: 
    Celery();
    rect getRect();
    void spawnCelery();
    void moveCelery();
};

#endif
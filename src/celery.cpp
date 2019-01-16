#include "celery.h"
#include <stdlib.h>
#include <time.h>

int randomC(int min, int max) {
    static bool first = true;

    if (first) {  
        srand(time(NULL));
        first = false;
    }

    return min + rand() % ((max + 1) - min);
}

void Celery::spawnCelery() {
    int celX = 100;
    int celY = 79;
    int screenX = 960;
    int screenY = 544;
    int celmin = 4;
    int celmax = 6;

    #ifdef PSP
    celX *= 0.5;
    celY *= 0.5;
    screenX *= 0.5;
    screenY *= 0.5;
    celmin *= 0.5;
    celmax *= 0.5;
    #endif

    celRect.x = randomC(0, screenX - celX);
    celRect.y = randomC(0, screenY - celY);
    celRect.hv = randomC(celmin, celmax);
    celRect.vv = randomC(celmin, celmax);
}

void Celery::moveCelery() {
    int screenwidth = 960;
    int screenheight = 544;

    #ifdef PSP
    screenwidth *= 0.5;
    screenheight *= 0.5;
    #endif

    celRect.x += celRect.hv;
    celRect.y += celRect.vv;

    if (celRect.x + celRect.w > screenwidth) {
        celRect.hv = -celRect.hv;
    } else if (celRect.x < 0) {
        celRect.hv = -celRect.hv;
    }

    if (celRect.y + celRect.h > screenheight) {
        celRect.vv = -celRect.vv;
    } else if (celRect.y < 0) {
        celRect.vv = -celRect.vv;
    }
} 

Celery::Celery() {
    int celX = 100;
    int celY = 79;

    #ifdef PSP
    celX *= 0.5;
    celY *= 0.5;
    #endif

    celRect.h = celY;
    celRect.w = celX;
}

rect Celery::getRect() {
    return celRect;
}
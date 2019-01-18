#include "celery.h"
#include "functions.h"
#include <stdlib.h>
#include <time.h>

void Celery::spawnCelery() {
    int celmin = 4;
    int celmax = 6;

    #ifdef PSP
    celmin *= 0.5;
    celmax *= 0.5;
    #endif

    celRect.x = random(0, getScreenRes(true) - celeryWidth);
    celRect.y = random(0, getScreenRes(false) - celeryHeight);
    celRect.hv = random(celmin, celmax);
    celRect.vv = random(celmin, celmax);
}

void Celery::moveCelery() {
    celRect.x += celRect.hv;
    celRect.y += celRect.vv;

    if (celRect.x + celRect.w > getScreenRes(true)) {
        celRect.hv = -celRect.hv;
    } else if (celRect.x < 0) {
        celRect.hv = -celRect.hv;
    }

    if (celRect.y + celRect.h > getScreenRes(false)) {
        celRect.vv = -celRect.vv;
    } else if (celRect.y < 0) {
        celRect.vv = -celRect.vv;
    }
} 

Celery::Celery() {
    celeryWidth = 100;
    celeryHeight = 79;
    #ifdef PSP
    celeryWidth *= 0.5;
    celeryHeight *= 0.5;
    #endif

    celRect.h = celeryHeight;
    celRect.w = celeryWidth;
}

rect Celery::getRect() {
    return celRect;
}
#include "graphics.h"
#include "inputHelper.h"
#include "nicCage.h"
#include "chicken.h"
#include "celery.h"
#include "collide.h"
#include "functions.h"

#include <vector>
#include <iostream>

int gameState;
bool gameInit;

//entities
NicCage nic;
Chicken chic;
std::vector<Celery> cel;
int celCount;

//gameplay
int celeryEaten;
bool translucent;

//nic cage hitbox adjustment
int hitDifX = 30;
int hitDifY = 70;

//images
#ifdef PSP
OSL_IMAGE *nicCageFace = NULL;
OSL_IMAGE *nicCageFaceTranslucent = NULL;
OSL_IMAGE *chicken = NULL;
OSL_IMAGE *celery = NULL;
#else
vita2d_texture *nicCageFace = NULL;
vita2d_texture *nicCageFaceTranslucent = NULL;
vita2d_texture *chicken = NULL;
vita2d_texture *celery = NULL;
vita2d_pgf *pgf;
#endif

void restartGame() {
    chic.chickenEaten = 0;
    celeryEaten = 0;
    chic.spawnChicken();
}

void cleanupGame() {
    freeImage(nicCageFace);
    freeImage(nicCageFaceTranslucent);
    freeImage(chicken);
    freeImage(celery);
}

void gameInput() {
    if (getButton(FACE_CIRCLE, 0)) {
        gameState = 2;
        cleanupGame();
    }

    if (getButton(FACE_CROSS, 1)) {
        translucent = true;
    } else {
        translucent = false;
    }

    if (getButton(DPAD_LEFT, 1) && !translucent)
        nic.moveX(-5);
    if (getButton(DPAD_RIGHT, 1) && !translucent)
        nic.moveX(5);
    if (getButton(DPAD_DOWN, 1) && !translucent)
        nic.moveY(5);
    if(getButton(DPAD_UP, 1) && !translucent)
        nic.moveY(-5);
}

void initGame() {
    Celery newcel;
    //images
    nicCageFace = defineImage("gfx/NicCageFace.png");
    nicCageFaceTranslucent = defineImage("gfx/NicCageFaceTranslucent.png");
    chicken = defineImage("gfx/chicken.png");
    celery = defineImage("gfx/celery.png");

    //throw some stuff in the world
    chic.spawnChicken();
    newcel.spawnCelery();

    // push new celery to vector
    cel.push_back(newcel);
    celCount++;

    //adjust some sizes for psp (and font)
    #ifdef PSP
    hitDifX *= 0.5;
    hitDifY *= 0.5;
    oslSetBkColor(RGBA(0, 0, 0, 0));
    oslSetTextColor(RGBA(0, 0, 0, 255));
    #else //vita font
    pgf = vita2d_load_default_pgf();
    #endif
}

void runGame() {
    if (!gameInit) {
        initGame();
        gameInit = true;
    }

    drawRect(0, 0, getScreenRes(true), getScreenRes(false), 255, 255, 255);

    if (translucent)
        drawImage(nicCageFaceTranslucent, nic.getRect().x - hitDifX, nic.getRect().y - hitDifY, 1, 1);
    else
        drawImage(nicCageFace, nic.getRect().x - hitDifX, nic.getRect().y - hitDifY, 1, 1);

    drawImage(chicken, chic.getRect().x, chic.getRect().y, 1, 1);

    for (int i = 0; i < celCount; ++i) {
        drawImage(celery, cel[i].getRect().x, cel[i].getRect().y, 1, 1);
        cel[i].moveCelery();
    }

    #ifdef PSP
    oslSetTextColor(RGBA(255, 0, 0, 255));
    oslDrawStringf(25, 15, "Don't eat Celery: %i/3", celeryEaten);
    oslSetTextColor(RGBA(0, 0, 0, 255));
    oslDrawStringf(25, 25, "Chicken Legs Eaten: %i", chic.chickenEaten);
    #else
    vita2d_pgf_draw_textf(pgf, 50, 30, RGBA8(255, 0, 0, 255), 1.0f, "Don't eat Celery: %d/3", celeryEaten);
    vita2d_pgf_draw_textf(pgf, 50, 50, RGBA8(0, 0, 0, 255), 1.0f, "Chicken Legs Eaten: %d", chic.chickenEaten);
    #endif

    if (checkCollison(nic.getRect(), chic.getRect())) {
        chic.spawnChicken();
        chic.chickenEaten++;

        if (chic.chickenEaten % 3 == 0) {
            Celery newcel;
            newcel.spawnCelery();
            cel.push_back(newcel);
            celCount++;
        }
    }

    for (int i = 0; i < celCount; ++i) {
        if (checkCollision(nic.getRect(), cel[i].getRect()) && !translucent) {
            cel.clear();

            for (int i = 0; i < celCount+1; ++i) {
                Celery newcel;
                newcel.spawnCelery();
                cel.push_back(newcel);
            }

            celeryEaten++;

            if (celeryEaten == 3) {
                gameState = 1;
            }
        }
    }

    gameInput(); //keep as a separate function (cleaner)
}
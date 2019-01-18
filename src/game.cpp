#include "graphics.h"
#include "inputHelper.h"
#include "nicCage.h"
#include "chicken.h"
#include "celery.h"
#include "collide.h"
#include "functions.h"

int gameState;
bool gameInit;

//entities
NicCage nic;
Chicken chic;
Celery cel;

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
#endif

void cleanupGame() {
    freeImage(nicCageFace);
    freeImage(nicCageFaceTranslucent);
    freeImage(chicken);
    freeImage(celery);
}

void gameInput() {
    if (getButton(FACE_CIRCLE, 0)) {
        gameState = 1;
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
    //images
    nicCageFace = defineImage("gfx/NicCageFace.png");
    nicCageFaceTranslucent = defineImage("gfx/NicCageFaceTranslucent.png");
    chicken = defineImage("gfx/chicken.png");
    celery = defineImage("gfx/celery.png");

    //throw some stuff in the world
    chic.spawnChicken();
    cel.spawnCelery();

    //adjust some sizes for psp
    #ifdef PSP
    hitDifX *= 0.5;
    hitDifY *= 0.5;
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
    drawImage(celery, cel.getRect().x, cel.getRect().y, 1, 1);
    cel.moveCelery();

    #ifdef PSP
    oslDrawString(0, 240, "DEBUG");
    oslDrawStringf(0, 250, "Joystick x %i", getJoyStickX());
    oslDrawStringf(0, 260, "Joystick y %i", getJoyStickY());
    #endif

    if (checkCollison(nic.getRect(), chic.getRect())) {
        chic.spawnChicken();
        chic.chickenEaten++;

        if (chic.chickenEaten == 3) {
            cel.spawnCelery();
        }
    }

    if (checkCollision(nic.getRect(), cel.getRect()) && !translucent) {
        cel.spawnCelery();
        celeryEaten++;
    }

    gameInput(); //keep as a separate function (cleaner)
}
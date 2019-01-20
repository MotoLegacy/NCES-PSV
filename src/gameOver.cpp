#include "functions.h"
#include "game.h"
#include "graphics.h"
#include "inputHelper.h"

bool goInit;
#ifndef PSP
vita2d_pgf *pgff;
#else
int width1;
int width2;
#endif

void gameOverInput() {
    if (getButton(FACE_CIRCLE, 0)) {
        gameState = 2;
        cleanupGame();
    }

    if (getButton(FACE_CROSS, 1)) {
        gameState = 0;
        restartGame();
    }
}

void initGameOver() {
    #ifndef PSP
    pgff = vita2d_load_default_pgf();
    #else
    width1 = oslGetStringWidth("Game Over!!!");
    width2 = oslGetStringWidth("Press X to Restart and O to Quit");
    #endif
}

void runGameOver() {
    if (!goInit) {
        initGameOver();
        goInit = true;
    }

    drawRect(0, 0, getScreenRes(true), getScreenRes(false), 255, 255, 255);
    #ifndef PSP
    vita2d_pgf_draw_text(pgff, 960 / 2 - vita2d_pgf_text_width(pgff, 1.0f, "Game Over!!!") / 2, 262, RGBA8(255, 0, 0, 255), 1.0f, "Game Over!!!");
    vita2d_pgf_draw_text(pgff, 960 / 2 - vita2d_pgf_text_width(pgff, 1.0f, "Press X to Restart and O to Quit") / 2, 282, RGBA8(29, 116, 25, 255), 1.0f, "Press X to Restart and O to Quit");
    #else
    oslSetTextColor(RGBA(255, 0, 0, 255));
    oslDrawStringf((getScreenRes(true) - width1)/2, 121, "Game Over!!!");
    oslSetTextColor(RGBA(29, 116, 25, 255));
    oslDrawStringf((getScreenRes(true) - width2)/2, 131, "Press X to Restart and O to Quit");
    #endif

    gameOverInput();
}
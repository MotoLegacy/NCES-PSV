#include "nicCage.h"

NicCage::NicCage() {
    nicRect.x = 0;
    nicRect.y = 0;
    nicRect.h = 20;
    nicRect.w = 20;
}

void NicCage::moveX(int vel){
    int screenwidth = 960;
    int cageWidth = 100;

    #ifdef PSP
    vel *= 0.65;
    screenwidth *= 0.5;
    cageWidth *= 0.5;
    #endif

    nicRect.x += vel;

    if (nicRect.x > screenwidth) {
        nicRect.x = 0;
    } else if (nicRect.x + cageWidth < 0) {
        nicRect.x = screenwidth;
    }
}

void NicCage::moveY(int vel) {
    int screenheight = 544;
    int cageHeight = 124;

    #ifdef PSP
    vel *= 0.65;
    screenheight *= 0.5;
    cageHeight *= 0.5;
    #endif

    nicRect.y += vel;

    if (nicRect.y > screenheight) {
        nicRect.y = 0;
    } else if (nicRect.y + cageHeight < 0) {
        nicRect.y = screenheight;
    }
}

rect NicCage::getRect() {
    return nicRect;
}
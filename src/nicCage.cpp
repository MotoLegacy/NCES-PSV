#include "nicCage.h"

NicCage::NicCage() {
    nicRect.x = 0;
    nicRect.y = 0;
    nicRect.h = 20;
    nicRect.w = 20;
}

void NicCage::moveX(int vel){
    #ifdef PSP
    vel *= 0.65;
    #endif

    nicRect.x += vel;
}

void NicCage::moveY(int vel) {
    #ifdef PSP
    vel *= 0.65;
    #endif

    nicRect.y += vel;
}

rect NicCage::getRect() {
    return nicRect;
}
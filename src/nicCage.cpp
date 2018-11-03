#include "nicCage.h"

NicCage::NicCage(){
    nicRect.x = 20;
    nicRect.y = 20;
    nicRect.h = 20;
    nicRect.w = 20;
}

void NicCage::moveX(int vel){
    nicRect.x += vel;
}

void NicCage::moveY(int vel) {
    nicRect.y += vel;
}

rect NicCage::getRect(){
    return nicRect;
}
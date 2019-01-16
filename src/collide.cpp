#include "collisionHelper.h"

bool checkCollison(rect a, rect b) {
    double leftA, leftB;
    double rightA, rightB;
    double topA, topB;
    double bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB)
       return false;

    if (topA >= bottomB)
        return false;

    if (rightA <= leftB)
        return false;

    if (leftA >= rightB)
        return false;


    return true;
}
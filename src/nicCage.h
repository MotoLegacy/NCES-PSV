#ifndef _NIC_CAGE_
#define _NIC_CAGE_

#include "collisionHelper.h"
class NicCage{
private: 
    rect nicRect;
public: 
    NicCage();
    rect getRect();
    void moveY(int vel);
    void moveX(int vel);
};

#endif
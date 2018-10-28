/*
    InputHelper.cpp - handles button inputs
*/

#include "inputHelper.h"

//FIXME - find a better way for input. This will do for now, though.
//v2.0 this should be priority :)

bool getButton(int button) {
    #ifdef PSP
    oslReadKeys();
    switch(button) {
        case FACE_CROSS:
            if (osl_keys->pressed.cross)
                return true;
        case FACE_CIRCLE:
            if (osl_keys->pressed.circle)
                return true;
        case FACE_SQUARE:
            if (osl_keys->pressed.square)
                return true;
        case FACE_TRIANGLE:
            if (osl_keys->pressed.triangle)
                return true;
        case DPAD_UP:
            if (osl_keys->pressed.up)
                return true;
        case DPAD_DOWN:
            if (osl_keys->pressed.down)
                return true;
        case DPAD_LEFT:
            if (osl_keys->pressed.left)
                return true;
        case DPAD_RIGHT:
            if (osl_keys->pressed.right)
                return true;
        default: return false;
    }
#else
    SceCtrlData pad;
    memset(&pad, 0, sizeof(pad));
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    sceCtrlPeekBufferPositive(0, &pad, 1);
    switch(button) {
        case FACE_CROSS:
            if(pad.buttons & SCE_CTRL_CROSS)
                return true;
        case FACE_CIRCLE:
            if(pad.buttons & SCE_CTRL_CIRCLE)
                return true;
        case FACE_SQUARE:
            if(pad.buttons & SCE_CTRL_SQUARE)
                return true;
        case FACE_TRIANGLE:
            if(pad.buttons & SCE_CTRL_TRIANGLE)
                return true;
        case DPAD_UP:
            if(pad.buttons & SCE_CTRL_UP)
                return true;
        case DPAD_DOWN:
            if(pad.buttons & SCE_CTRL_DOWN)
                return true;
        case DPAD_LEFT:
            if(pad.buttons & SCE_CTRL_LEFT)
                return true;
        case DPAD_RIGHT:
            if(pad.buttons & SCE_CTRL_RIGHT)   
                return true;
        default: return false;
    }
    #endif
    return false;
}


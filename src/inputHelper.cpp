/*
    InputHelper.cpp - handles button inputs
*/

#include "inputHelper.h"

//FIXME - find a better way for input. This will do for now, though.
//v2.0 this should be priority :)

bool getButton(int button, int hold) {
    #ifdef PSP
    oslReadKeys();
    switch(button) {
        case FACE_CROSS:
            if (hold) {
                if (osl_keys->held.cross)
                    return true;
            } else {
                if (osl_keys->pressed.cross)
                    return true;
            }
            break;
        case FACE_CIRCLE:
            if (hold) {
                if (osl_keys->held.circle)
                    return true;
            } else {
                if (osl_keys->pressed.circle)
                    return true;
            }
            break;
        case FACE_SQUARE:
            if (hold) {
                if (osl_keys->held.square)
                    return true;
            } else {
                if (osl_keys->pressed.square)
                    return true;
            }
            break;
        case FACE_TRIANGLE:
            if (hold) {
                if (osl_keys->held.triangle)
                    return true;
            } else {
                if (osl_keys->pressed.triangle)
                    return true;
            }
            break;
        case DPAD_UP:
            if (hold) {
                if (osl_keys->held.up)
                    return true;
            } else {
                if (osl_keys->pressed.up)
                    return true;
            }
            break;
        case DPAD_DOWN:
            if (hold) {
                if (osl_keys->held.down)
                    return true;
            } else {
                if (osl_keys->pressed.down)
                    return true;
            }
            break;
        case DPAD_LEFT:
            if (hold) {
                if (osl_keys->held.left)
                    return true;
            } else {
                if (osl_keys->pressed.left)
                    return true;
            }
            break;
        case DPAD_RIGHT:
            if (hold) {
                if (osl_keys->held.right)
                    return true;
            } else {
                if (osl_keys->pressed.right)
                    return true;
            }
            break;
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
            break; //need breaks because this function is being called every frame
        case FACE_CIRCLE:
            if(pad.buttons & SCE_CTRL_CIRCLE)
                return true;
            break;
        case FACE_SQUARE:
            if(pad.buttons & SCE_CTRL_SQUARE)
                return true;
            break;
        case FACE_TRIANGLE:
            if(pad.buttons & SCE_CTRL_TRIANGLE)
                return true;
            break; 
        case DPAD_UP:
            if(pad.buttons & SCE_CTRL_UP)
                return true;
            break;
        case DPAD_DOWN:
            if(pad.buttons & SCE_CTRL_DOWN)
                return true;
            break;
        case DPAD_LEFT:
            if(pad.buttons & SCE_CTRL_LEFT)
                return true;
            break;
        case DPAD_RIGHT:
            if(pad.buttons & SCE_CTRL_RIGHT)
                return true;
            break;
        default: return false;
    }
    #endif
    return false;
}

int getJoyStickX() {
    #ifdef PSP
    oslReadKeys();
    return osl_keys->analogX;

    #else 
    SceCtrlData pad;
    memset(&pad, 0, sizeof(pad));
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    sceCtrlPeekBufferPositive(0, &pad, 1);
    return pad.lx - 255;

    #endif
}

int getJoyStickY() {
    #ifdef PSP
    oslReadKeys();
    return osl_keys->analogY;

    #else 
    SceCtrlData pad;
    memset(&pad, 0, sizeof(pad));
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    sceCtrlPeekBufferPositive(0, &pad, 1);
    return pad.ly - 255;

    #endif
}


#include "graphics.h"
#include "inputHelper.h"
#include "nicCage.h"

#ifdef PSP
    PSP_MODULE_INFO("NCESPSP", 0, 1, 0);
    PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
    PSP_HEAP_SIZE_KB(12*1024);
#endif

int main() 
{   
    init();
    int skip = 0;
    bool quit = false;
    NicCage nic;
    #ifdef PSP
    OSL_IMAGE *nicCageFace = NULL;
    int screen_width = 480;
    int screen_height = 272;
    #else 
    vita2d_texture *nicCageFace = NULL;
    int screen_width = 960;
    int screen_height = 544;
    #endif

    nicCageFace = defineImage("gfx/NicCageFace.png");

    while(!quit){
        if(!skip){
            startDrawing();
            drawRect(0, 0, screen_width, screen_height, 255, 255, 255);
            drawImage(nicCageFace, nic.getRect().x, nic.getRect().y, 1, 1);
            #ifdef PSP
            oslDrawStringf(0, 0, "Joystick x %i", getJoyStickX());
            oslDrawStringf(0, 30, "Joystick y %i", getJoyStickY());
            #endif
            endDrawing();
        }
        skip = syncFrame();

        if (getButton(FACE_CROSS))
            quit = true;
        if (getButton(DPAD_LEFT))
            nic.moveX(-5);
        if (getButton(DPAD_RIGHT))
            nic.moveX(5);
        if (getButton(DPAD_DOWN))
            nic.moveY(5);
        if(getButton(DPAD_UP))
            nic.moveY(-5);
    }

    #ifdef PSP
    oslDeleteImage(nicCageFace);
    oslEndGfx();
    oslQuit();
    #else
    vita2d_fini();
	vita2d_free_texture(nicCageFace);
    sceKernelExitProcess(0);
    #endif    
    return 0;
}
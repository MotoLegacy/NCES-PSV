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
    bool translucent = false;
    NicCage nic;

    int screen_width = 960;
    int screen_height = 544;

    #ifdef PSP
    OSL_IMAGE *nicCageFace = NULL;
    OSL_IMAGE *nicCageFaceTranslucent = NULL;
    screen_width *= 0.5;
    screen_height *= 0.5;
    #else
    vita2d_texture *nicCageFace = NULL;
    vita2d_texture *nicCageFaceTranslucent = NULL;
    #endif

    nicCageFace = defineImage("gfx/NicCageFace.png");
    nicCageFaceTranslucent = defineImage("gfx/NicCageFaceTranslucent.png");

    while(!quit){
        if(!skip){
            startDrawing();
            drawRect(0, 0, screen_width, screen_height, 255, 255, 255);

            if (translucent)
                drawImage(nicCageFaceTranslucent, nic.getRect().x, nic.getRect().y, 1, 1);
            else
                drawImage(nicCageFace, nic.getRect().x, nic.getRect().y, 1, 1);

            #ifdef PSP
            oslDrawStringf(0, 0, "Joystick x %i", getJoyStickX());
            oslDrawStringf(0, 30, "Joystick y %i", getJoyStickY());
            #endif
            endDrawing();
        }
        skip = syncFrame();

        if (getButton(FACE_CROSS, 1)) {
            translucent = true;
        } else {
            translucent = false;
        }

        if (getButton(FACE_CIRCLE, 0))
            quit = true;
        if (getButton(DPAD_LEFT, 1) && !translucent)
            nic.moveX(-5);
        if (getButton(DPAD_RIGHT, 1) && !translucent)
            nic.moveX(5);
        if (getButton(DPAD_DOWN, 1) && !translucent)
            nic.moveY(5);
        if(getButton(DPAD_UP, 1) && !translucent)
            nic.moveY(-5);
    }

    freeImage(nicCageFace);

    #ifdef PSP
    //oslDeleteImage(nicCageFace);
    oslEndGfx();
    oslQuit();
    #else
    vita2d_fini();
	//vita2d_free_texture(nicCageFace);
    sceKernelExitProcess(0);
    #endif  

    return 0;
}
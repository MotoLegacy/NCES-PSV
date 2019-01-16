#include "graphics.h"
#include "inputHelper.h"
#include "nicCage.h"
#include "chicken.h"

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
    Chicken chic;

    int screen_width = 960;
    int screen_height = 544;

    #ifdef PSP
    OSL_IMAGE *nicCageFace = NULL;
    OSL_IMAGE *nicCageFaceTranslucent = NULL;
    OSL_IMAGE *chicken = NULL;
    screen_width *= 0.5;
    screen_height *= 0.5;
    #else
    vita2d_texture *nicCageFace = NULL;
    vita2d_texture *nicCageFaceTranslucent = NULL;
    vita2d_texture *chicken = NULL;
    #endif

    nicCageFace = defineImage("gfx/NicCageFace.png");
    nicCageFaceTranslucent = defineImage("gfx/NicCageFaceTranslucent.png");
    chicken = defineImage("gfx/chicken.png");

    chic.spawnChicken();

    while(!quit){
        if(!skip){
            startDrawing();
            drawRect(0, 0, screen_width, screen_height, 255, 255, 255);

            if (translucent)
                drawImage(nicCageFaceTranslucent, nic.getRect().x, nic.getRect().y, 1, 1);
            else
                drawImage(nicCageFace, nic.getRect().x, nic.getRect().y, 1, 1);

            drawImage(chicken, chic.getRect().x, chic.getRect().y, 1, 1);

            #ifdef PSP
            oslDrawString(0, 240, "DEBUG");
            oslDrawStringf(0, 250, "Joystick x %i", getJoyStickX());
            oslDrawStringf(0, 260, "Joystick y %i", getJoyStickY());
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
    oslEndGfx();
    oslQuit();
    #else
    vita2d_fini();
    sceKernelExitProcess(0);
    #endif  

    return 0;
}
#include "graphics.h"
#include "inputHelper.h"
#include "nicCage.h"
#include "chicken.h"
#include "celery.h"
#include "collide.h"

/*
    TODO:
        1. clean up main
        2. make celery an array (to have multiple)
        3. remove copy/paste code
        4. vita2d draw text
*/

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
    Celery cel;

    int screen_width = 960;
    int screen_height = 544;

    int celeryEaten = 0;

    int hitDifX = 30;
    int hitDifY = 70;

    #ifdef PSP
    OSL_IMAGE *nicCageFace = NULL;
    OSL_IMAGE *nicCageFaceTranslucent = NULL;
    OSL_IMAGE *chicken = NULL;
    OSL_IMAGE *celery = NULL;
    screen_width *= 0.5;
    screen_height *= 0.5;
    hitDifX *= 0.5;
    hitDifY *= 0.5;
    #else
    vita2d_texture *nicCageFace = NULL;
    vita2d_texture *nicCageFaceTranslucent = NULL;
    vita2d_texture *chicken = NULL;
    vita2d_texture *celery = NULL;
    #endif

    nicCageFace = defineImage("gfx/NicCageFace.png");
    nicCageFaceTranslucent = defineImage("gfx/NicCageFaceTranslucent.png");
    chicken = defineImage("gfx/chicken.png");
    celery = defineImage("gfx/celery.png");

    chic.spawnChicken();
    cel.spawnCelery();

    while(!quit){
        if(!skip){
            startDrawing();
            drawRect(0, 0, screen_width, screen_height, 255, 255, 255);

            if (translucent)
                drawImage(nicCageFaceTranslucent, nic.getRect().x - hitDifX, nic.getRect().y - hitDifY, 1, 1);
            else
                drawImage(nicCageFace, nic.getRect().x - hitDifX, nic.getRect().y - hitDifY, 1, 1);

            drawImage(chicken, chic.getRect().x, chic.getRect().y, 1, 1);
            drawImage(celery, cel.getRect().x, cel.getRect().y, 1, 1);
            cel.moveCelery();

            #ifdef PSP
            oslDrawString(0, 240, "DEBUG");
            oslDrawStringf(0, 250, "Joystick x %i", getJoyStickX());
            oslDrawStringf(0, 260, "Joystick y %i", getJoyStickY());
            #endif

            if (checkCollison(nic.getRect(), chic.getRect())) {
                chic.spawnChicken();
                chic.chickenEaten++;

                if (chic.chickenEaten == 3) {
                    cel.spawnCelery();
                }
            }

            if (checkCollision(nic.getRect(), cel.getRect()) && !translucent) {
                cel.spawnCelery();
                celeryEaten++;
            }

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
    freeImage(nicCageFaceTranslucent);
    freeImage(chicken);
    freeImage(celery);

    #ifdef PSP
    oslEndGfx();
    oslQuit();
    #else
    vita2d_fini();
    sceKernelExitProcess(0);
    #endif  

    return 0;
}
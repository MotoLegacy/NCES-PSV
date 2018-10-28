#include "graphics.h"
#include "inputHelper.h"

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
    #ifdef PSP
    OSL_IMAGE *testImg = NULL;
    #else 
    vita2d_texture *testImg = NULL;
    #endif

    testImg = defineImage("gfx/test.png");

    while(!quit){
        if(!skip){
            startDrawing();
            drawImage(testImg, 0, 0, 1, 1);
            #ifdef PSP
            oslDrawStringf(0, 0, "Joystick x %i", getJoyStickX());
            oslDrawStringf(0, 30, "Joystick y %i", getJoyStickY());
            #endif
            endDrawing();
        }
        skip = syncFrame();

        if (getButton(FACE_CROSS))
            quit = true;
    }

    #ifdef PSP
    oslDeleteImage(testImg);
    oslEndGfx();
    oslQuit();
    #else
    vita2d_fini();
	vita2d_free_texture(testImg);
    sceKernelExitProcess(0);
    #endif    
    return 0;
}
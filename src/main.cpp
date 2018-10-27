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
    #ifdef PSP
    OSL_IMAGE *testImg = NULL;
    #else 
    vita2d_texture *testImg = NULL;
    #endif

    testImg = defineImage("gfx/test.png");

    while(true){
        if(!skip){
            startDrawing();
            drawImage(testImg, 0, 0, 1, 1);
            endDrawing();
        }
        skip = syncFrame();

        #ifdef PSP
        oslReadKeys();
        if (getButton(FACE_CROSS))
            oslQuit();
        #endif
    }
    
    return 0;
}
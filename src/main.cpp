#include "graphics.h"
#include "game.h"
#include "gameOver.h"
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

    while (!quit) {
        if (!skip) {
            startDrawing();
            switch(gameState) {
                case 0:
                    runGame();
                    break;
                case 1:
                    runGameOver();
                    break;
                case 2:
                    quit = true;
                    break;

            }
            endDrawing();
        }
        skip = syncFrame();
    }

    #ifdef PSP
    oslEndGfx();
    oslQuit();
    #else
    cleanupGame();
    vita2d_fini();
    sceKernelExitProcess(0);
    #endif  

    return 0;
}
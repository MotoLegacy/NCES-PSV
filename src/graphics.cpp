/* 
    Graphics.cpp - handles image defining and drawing
*/
#include "graphics.h"
//-------------------PSP SECTION--------------------//
#ifdef PSP 

    OSL_IMAGE *defineImage(char *filename) {
    OSL_IMAGE *temp;
    temp = oslLoadImageFilePNG(filename, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

    return temp;
}

void drawImage(OSL_IMAGE *img, int x, int y, int scalex, int scaley) {
    oslDrawImageXY(img, x, y);
}
//-----------------VITA SECTION---------------------//
#else 

vita2d_texture *defineImage(const char *filename) {
    std::string a = "app0:/";
    a += filename;
    const char *fin = a.c_str();

    vita2d_texture* temp;
    temp = vita2d_load_PNG_file(fin);

    return temp;
}

void drawImage(const vita2d_texture *texture, float x, float y, float scalex, float scaley) {
    vita2d_draw_texture_scale(texture, x, y, scalex, scaley);
}

#endif
//------------------GENERAL SECTION----------------//
void init() {
    #ifdef PSP

    oslInit(0);
    oslInitGfx(OSL_PF_8888, 1);
    //oslSetTransparentColor(255, 0, 255); MOTO (FIXME) -- this causes errors.

    #else

    vita2d_init();
    vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));

    #endif
}

void startDrawing(){
    #ifdef PSP 

    oslStartDrawing();

    #else
    
    vita2d_start_drawing();
	vita2d_clear_screen();

    #endif
}

void endDrawing(){
    #ifdef PSP
    
    oslEndDrawing();

    #else 

    vita2d_end_drawing();
	vita2d_swap_buffers();

    #endif
}

int syncFrame(){
    #ifdef PSP

    oslEndFrame();
    return oslSyncFrame();

    #else 
    return 0;
    #endif
}

void drawRect(int x, int y, int w, int h, int r, int g, int b){
    #ifdef PSP 
    oslDrawFillRect(x, y, x + w, y + h, RGBA(r, g, b, 255));
    #else
    vita2d_draw_rectangle(x, y, w, h, RGBA8(r, g, b, 255));
    #endif
}
/* 
    Graphics.cpp - handles image defining and drawing
*/

#ifdef PSP //if the target platform is PSP

#include <pspkernel.h>
#include <oslib/oslib.h>

PSP_MODULE_INFO("Hello World", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(12*1024);

#else //we're not PSP according to the compiler, so we're the Vita

#include <vita2d.h>
#include <string>

#endif

//defining images
#ifdef PSP
OSL_IMAGE *defineImage(char *filename) {
    OSL_IMAGE *temp;
    temp = oslLoadImageFilePNG(filename, 0, 0);

    return temp;
}

#else

vita2d_texture *defineImage(const char *filename) {
    std::string a = "app0:/";
    a += filename;
    const char *fin = a.c_str();

    vita2d_texture* temp;
    temp = vita2d_load_PNG_file(fin);

    return temp;
}
#endif

//actually drawing images
#ifdef PSP

void drawImage(OSL_IMAGE *img, int x, int y, int scalex, int scaley) {
    oslDrawImageXY(img, x, y);
}

#else

void drawImage(const vita2d_texture *texture, float x, float y, float scalex, float scaley) {
    vita2d_draw_texture_scale(texture, x, y, scalex, scaley);
}

#endif

void initGfx() {
    #ifdef PSP

    oslInit(0);
    oslInitGfx(OSL_PF_8888, 1);
    //oslSetTransparentColor(255, 0, 255); MOTO (FIXME) -- this causes errors.

    #else

    vita2d_init();
    vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));

    #endif
}

int main() {
    return 0;
}
#ifndef _GRAPHICS_
#define _GRAPHICS_
//--------------------PSP SECTION------------------------//
#ifdef PSP

#include <pspkernel.h>
#include <oslib/oslib.h>

OSL_IMAGE *defineImage(char *filename);
void freeImage(OSL_IMAGE *img);

void drawImage(OSL_IMAGE *img, int x, int y, int scalex, int scaley);
//---------------------VITA SECTION----------------------//
#else

#include <vita2d.h>
#include <string>

vita2d_texture *defineImage(const char *filename);

void drawImage(const vita2d_texture *texture, float x, float y, float scalex, float scaley);
void freeImage(vita2d_texture *img);

#endif
//--------------------GENERAL SECTION-----------------------//
void init();
void startDrawing();
void endDrawing();
int syncFrame();
void drawRect(int x, int y, int w, int h, int r, int g, int b);

#endif
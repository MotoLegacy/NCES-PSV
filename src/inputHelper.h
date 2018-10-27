#ifndef _INPUTHELPER_
#define _INPUTHELPER_

#ifdef PSP

#include <pspkernel.h>
#include <oslib/oslib.h>

#else

#endif

/* ====================
    BUTTON DEFINITIONS
   ==================== */

//face buttons
#define FACE_CROSS      1
#define FACE_CIRCLE     2
#define FACE_SQUARE     3
#define FACE_TRIANGLE   4

//directional pad
#define DPAD_UP         5
#define DPAD_DOWN       6
#define DPAD_LEFT       7
#define DPAD_RIGHT      8

bool getButton(int button);

#endif
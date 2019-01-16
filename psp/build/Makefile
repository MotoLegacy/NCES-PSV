TARGET = NCESPSP
OBJS = ../../src/main.o ../../src/graphics.o ../../src/inputHelper.o ../../src/collisionHelper.o ../../src/nicCage.o ../../src/chicken.o ../../src/collide.o ../../src/celery.o

INCDIR = $(PSPPATH)/include
CFLAGS = -O3 -G0 -Wall -mpreferred-stack-boundary=4 #-enable-newlib-hw-fp -ffast-math
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PSP_FW_VERSION=371
PSP_LARGE_MEMORY = 1

LDFLAGS =
LIBS= -losl -lpng -lz \
         -lpsphprm -lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgu -lpspgum  -lpspaudiolib -lpspaudio -lpsphttp -lpspssl -lpspwlan \
         -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl -lm -ljpeg

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Nic Cage Eats Stuff
PSP_EBOOT_ICON = ICON0.png
PSP_EBOOT_PIC1 = PIC1.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
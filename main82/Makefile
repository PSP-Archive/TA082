release: all
	mksfo 'TA082 IdStorage Change' PARAM.SFO
	pack-pbp EBOOT.PBP PARAM.SFO NULL NULL NULL NULL NULL idstoragechange.prx NULL


TARGET = idstoragechange
OBJS = main.o pspTA082_driver.S

INCDIR = 
CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1

LIBDIR =
LIBS = -lpsppower
LDFLAGS =

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

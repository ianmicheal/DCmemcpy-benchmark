 
######################################################################
#               memcpy benchmark kos2.0 DreamCast  V 1.0             #
######################################################################
#																	 #
#																	 #
#								  Makefile (c)2022 from Ian Micheal  #
######################################################################

# Files --------------------------------------------------------------------------- -std=c99

TARGET = memcpymark.elf
BIN = memcpymark.bin
FIRSTREAD = memcpymark.bin
# Optimize -------------------------------------------------------------------------
//OPT= -DQUIET -DNDEBUG -O3 -g   -fstack-usage -Wstack-usage=512 -trigraphs  -ffast-math -mdiv=inv -maccumulate-outgoing-args -mpretend-cmove -Wl,--gc-sections 
OPT=   -std=c99 -O3  -ffast-math -ffp-contract=fast -fomit-frame-pointer -flto  -mpretend-cmove -falign-loops=4 -falign-labels=2 -falign-functions=32 -falign-jumps=2
# Defines -------------------------------------------------------------------------
KOS_LOCAL_CFLAGS = -DDC  -flto -fwhole-program  -DUSE_ZLIB -DDREAMCAST -DMAX_MEM_LEVEL -DSDL -DLSB_FIRST -DALIGN_LONG -DINLINE -DDC -DUCHAR_MAX=0xff -DUSHRT_MAX=0xffff -DULONG_MAX=0xffffffff
KOS_CFLAGS += $(OPT)
# Files ---------------------------------------------------------------------------
OBJS = bench.o memcpy.o 





all: rm-elf $(TARGET)
# Base ----------------------------------------------------------------------------
KOS_LOCAL_CFLAGS += -DDC
KOS_LOCAL_CFLAGS += -I$(KOS_BASE)/include/SDL_image
KOS_LOCAL_CFLAGS += -I$(KOS_BASE)/include/SDL_ttf
include $(KOS_BASE)/Makefile.rules

clean:
	-rm -f $(TARGET) $(BIN) $(FIRSTREAD) $(OBJS) romdisk.*

rm-elf:
	-rm -f $(TARGET) romdisk.*
# Link ----------------------------------------------------------------------------
$(TARGET): $(OBJS) $(SND_OBJS)  $(SOFT_OBJS) romdisk.o
	$(KOS_CC) -flto -fwhole-program $(KOS_CFLAGS) -flto -fwhole-program $(KOS_LDFLAGS) -flto -fwhole-program -o $(TARGET) -flto -fwhole-program $(KOS_START) \
		$(OBJS) $(SND_OBJS) $(SOFT_OBJS) romdisk.o $(OBJEXTRA) -flto -fwhole-program -L$(KOS_BASE)/lib   -lm -lz -lkallisti  -lc  $(KOS_LIBS)

# ROM Disk Creation ---------------------------------------------------------------
romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk -v

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist:
	rm -f $(OBJS) romdisk.o romdisk.img
	$(KOS_STRIP) $(TARGET)
	$(KOS_CC_BASE)/bin/sh-elf-objcopy -O binary $(TARGET) $(BIN)
	$(KOS_CC_BASE)/bin/sh-elf-scramble $(BIN) $(FIRSTREAD)

#	for optimize problem
#screen.o : screen.c
#	$(KOS_CC) $(KOS_CFLAGS) -c -O1 $<


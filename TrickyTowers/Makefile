#one-line comment
TARGET = hello
OBJS = main.o ClassBlock.o ClassLevel.o Backgrounds.o ClassGame.o timeManager.o ClassDraw.o ClassBlock.o ClassResourceManager.o ClassRenderer.o ClassCloud.o\
        ClassGara.o ClassRompicapo.o ClassBaseGara.o ClassBaseRompicapo.o ClassFlag.o ClassLaser.o ClassCamera.o ClassFlag.o MyContactListener.o ClassTimer.o\
        ClassAnimatedSprite.o ClassControls.o ClassBaseSopravvivenza.o ClassSopravvivenza.o ClassHearts.o ClassPausa.o
 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
 
LIBS=  -losl -ljpeg -lpng -lz -lBox2d\
         -lpsphprm -lpspsdk -lpspctrl -lpsprtc -lpsppower -lpspgu -lpspgum  -lpspaudiolib -lpspaudio  -lpspaudiocodec\
         -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl -lm -lstdc++

#EXTRA_TARGETS is the output file
#PSP_EBOOT_TITLE is the EBOOT's name
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Tricky Towers PSP
PSP_EBOOT_ICON= icon0.png
PSP_EBOOT_PIC1= pic0.png
 
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
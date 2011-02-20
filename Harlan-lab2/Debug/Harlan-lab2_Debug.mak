SHELL = cmd.exe

#
# ZDS II Make File - Harlan-lab2 project, Debug configuration
#
# Generated by: ZDS II - ZNEO 4.11.1 (Build 08081801)
#   IDE component: c:4.11:08081801
#   Install Path: C:\Program Files (x86)\ZiLOG\ZDSII_ZNEO_4.11.1\
#

RM = del

ZDS = C:\PROGRA~2\ZiLOG\ZDSII_~1.1
BIN = $(ZDS)\bin
# ZDS include base directory
INCLUDE = C:\PROGRA~2\ZiLOG\ZDSII_~1.1\include
# intermediate files directory
WORKDIR = C:\Users\Matt\Documents\CSCI-4415-labs\Harlan-lab2\Debug

CC = @$(BIN)\zneocc
AS = @$(BIN)\zneoasm
LD = @$(BIN)\zneolink
AR = @$(BIN)\zneolib

CFLAGS =  \
-chartype:U -define:_Z16F2811FI -define:_Z16F_SERIES -genprintf  \
-NOkeepasm -keeplst -NOlist -NOlistinc -model:S -NOmodsect  \
-stdinc:"C:\PROGRA~2\ZiLOG\ZDSII_~1.1\include\std;C:\PROGRA~2\ZiLOG\ZDSII_~1.1\include\zilog"  \
-usrinc:"..\include" -regvar -NOreduceopt -warn -debug  \
-cpu:Z16F2811FI  \
-asmsw:" -cpu:Z16F2811FI -define:_Z16F2811FI=1 -define:_Z16F_SERIES=1 -include:C:\PROGRA~2\ZiLOG\ZDSII_~1.1\include\std;C:\PROGRA~2\ZiLOG\ZDSII_~1.1\include\zilog"

ASFLAGS =  \
-define:_Z16F2811FI=1 -define:_Z16F_SERIES=1  \
-include:"C:\PROGRA~2\ZiLOG\ZDSII_~1.1\include\std;C:\PROGRA~2\ZiLOG\ZDSII_~1.1\include\zilog"  \
-list -NOlistmac -name -pagelen:56 -pagewidth:80 -quiet -warn  \
-debug -NOigcase -cpu:Z16F2811FI

LDFLAGS = @.\Harlan-lab2_Debug.linkcmd
OUTDIR = C:\Users\Matt\Documents\CSCI-4415-labs\Harlan-lab2\Debug

build: Harlan-lab2

buildall: clean Harlan-lab2

relink: deltarget Harlan-lab2

deltarget: 
	@if exist $(WORKDIR)\Harlan-lab2.lod  \
            $(RM) $(WORKDIR)\Harlan-lab2.lod
	@if exist $(WORKDIR)\Harlan-lab2.hex  \
            $(RM) $(WORKDIR)\Harlan-lab2.hex
	@if exist $(WORKDIR)\Harlan-lab2.map  \
            $(RM) $(WORKDIR)\Harlan-lab2.map

clean: 
	@if exist $(WORKDIR)\Harlan-lab2.lod  \
            $(RM) $(WORKDIR)\Harlan-lab2.lod
	@if exist $(WORKDIR)\Harlan-lab2.hex  \
            $(RM) $(WORKDIR)\Harlan-lab2.hex
	@if exist $(WORKDIR)\Harlan-lab2.map  \
            $(RM) $(WORKDIR)\Harlan-lab2.map
	@if exist $(WORKDIR)\speaker.obj  \
            $(RM) $(WORKDIR)\speaker.obj

# pre-4.11.0 compatibility
rebuildall: buildall 

LIBS = 

OBJS =  \
            $(WORKDIR)\speaker.obj

Harlan-lab2: $(OBJS)
	 $(LD) $(LDFLAGS)

$(WORKDIR)\speaker.obj :  \
            C:\Users\Matt\Documents\CSCI-4415-labs\Harlan-lab2\speaker.c  \
            C:\Users\Matt\Documents\CSCI-4415-labs\Harlan-lab2\include\speaker.h
	 $(CC) $(CFLAGS) C:\Users\Matt\Documents\CSCI-4415-labs\Harlan-lab2\speaker.c

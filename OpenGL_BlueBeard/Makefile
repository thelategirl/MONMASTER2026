#  Makefile 
#  Auteur : Farès BELHADJ
#  Modifications : EKOMONO Anyce
# définition des commandes utilisées
CC = gcc
ECHO = echo
RM = rm -f
TAR = tar
ZIP = zip
MKDIR = mkdir
CHMOD = chmod
CP = rsync -R
# déclaration des options du compilateur
CFLAGS = -Wall -O3
CPPFLAGS = -I.
LDFLAGS = -lm -lSDL2_ttf
UPX = upx
UPXFLAGS = --best
# définition des fichiers et dossiers
PACKNAME = Demo
PROGNAME = BlueBeard
VERSION = 1.0
distdir = $(PACKNAME)_$(PROGNAME)-$(VERSION)
HEADERS = animations.h audioHelper.h
SOURCES = animations.c audioHelper.c window.c texte_intro.c intro.c chandelier.c eyes.c snake.c buzz.c blood.c
MSVCSRC = $(patsubst %,<ClCompile Include=\"%\\\" \\/>,$(SOURCES))
OBJ = $(SOURCES:.c=.o)
EXTRAFILES = $(wildcard shaders/*.?s images/*.png) $(VSCFILES) Basic5.woff2 metronome-65396.mid
DISTFILES = $(SOURCES) Makefile $(HEADERS) $(EXTRAFILES)
# Traitements automatiques pour ajout de chemins et options (ne pas modifier)
ifneq (,$(shell ls -d /usr/local/include 2>/dev/null | tail -n 1))
	CPPFLAGS += -I/usr/local/include
endif
ifneq (,$(shell ls -d $(HOME)/local/include 2>/dev/null | tail -n 1))
	CPPFLAGS += -I$(HOME)/local/include
endif
ifneq (,$(shell ls -d /usr/local/lib 2>/dev/null | tail -n 1))
	LDFLAGS += -L/usr/local/lib
endif
ifneq (,$(shell ls -d $(HOME)/local/lib 2>/dev/null | tail -n 1))
	LDFLAGS += -L$(HOME)/local/lib
endif
ifeq ($(shell uname),Darwin)
	MACOSX_DEPLOYMENT_TARGET = 11.0
        CFLAGS += -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET)
        LDFLAGS += -framework OpenGL -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET)
else
        LDFLAGS += -lGL
endif
CPPFLAGS += $(shell sdl2-config --cflags)
LDFLAGS  += -lGL4Dummies $(shell sdl2-config --libs) -lSDL2_mixer
all: $(PROGNAME)
$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)
	@echo ">>> Compression de $(PROGNAME) avec UPX..."
	@$(UPX) $(UPXFLAGS) $@
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
dist: distdir
	$(CHMOD) -R a+r $(distdir)
	$(TAR) zcvf $(distdir).tgz $(distdir)
	$(RM) -r $(distdir)
zip: distdir
	$(CHMOD) -R a+r $(distdir)
	$(ZIP) -r $(distdir).zip $(distdir)
	$(RM) -r $(distdir)
distdir: $(DISTFILES)
	$(RM) -r $(distdir)
	$(MKDIR) $(distdir)
	$(CHMOD) 777 $(distdir)
	$(CP) $(DISTFILES) $(distdir)
clean:
	@$(RM) -r $(PROGNAME) $(OBJ) *~ $(distdir).tgz $(distdir).zip gmon.out	\
	  core.* documentation/*~ shaders/*~ documentation/html

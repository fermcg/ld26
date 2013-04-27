# Compiler
CC=g++

# Directories
INCDIR=./include
SRCDIR=./src
OBJDIR=./obj

# SDL 2.0
SDL2-CFLAGS=`sdl2-config --cflags`
SDL2-LDFLAGS=`sdl2-config --libs` -lSDL2_image -lSDL2_mixer

# Base System Objects
BASEOBJ=exceptions.o singletons.o base_system.o config.o config_map.o \
		config_section.o 

# Game Objects
GAMEOBJ=game_system.o game_loop.o game_object.o screen.o sprite.o \
		sprite_map.o player.o texture.o texture_map.o all_objects.o \
		aux_functions.o accelerable_object.o enemy.o player_shot.o \
		projectile.o sprite_sequence.o sprite_face.o sound_effect.o \
		sound_effects_map.o

# texture_map.o
# TimeLord
TLCFLAGS=-I$(INCDIR)
TLLDFLAGS=-lm
_TLOBJS=main.o $(BASEOBJ) $(GAMEOBJ)
TLOBJS=$(patsubst %,$(OBJDIR)/%,$(_TLOBJS))

# Test
_TESTOBJS=test.o
TESTOBJS=$(patsubst %,$(OBJDIR)/%,$(_TESTOBJS))

# All
CFLAGS=$(SDL2-CFLAGS) $(TLCFLAGS) -g
LDFLAGS=$(SDL2-LDFLAGS) $(TLLDFLAGS)
OBJS=$(TL-OBJS)

# All targets
all: ld26

# Obj Rule
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

# TimeLord target
ld26: $(TLOBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

test: $(TESTOBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o core ld26 test
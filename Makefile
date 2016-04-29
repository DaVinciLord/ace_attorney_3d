CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror `sdl2-config --cflags` -D_XOPEN_SOURCE=700 -pthread
LDLIBS = -lm -lGLU -lGL `sdl2-config --libs` -lSDL2_image -pthread
all: courtroom

courtroom: courtroom.h
clean:
	$(RM) *.o *~ courtroom

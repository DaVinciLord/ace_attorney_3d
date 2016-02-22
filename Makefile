CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror `sdl2-config --cflags`
LDLIBS = -lm -lGLU -lGL `sdl2-config --libs`

all: courtroom

clean:
	$(RM) *.o *~ courtroom

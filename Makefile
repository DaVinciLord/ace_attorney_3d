CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror `sdl2-config --cflags`
LDLIBS = -lm -lGLU -lGL `sdl2-config --libs` -lSDL2_image

all: courtroom 

clean:
	$(RM) *.o *~ courtroom

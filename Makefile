CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror `sdl2-config --cflags` -D_XOPEN_SOURCE=700 -pthread
LDLIBS = -lm -lGLU -lGL `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -pthread
LIBS = libCourtroom.a

all: $(LIBS)

courtroom: courtroom.c all
	gcc $(CFLAGS) $< $(LDLIBS) $(LIBS)  -o courtroom

libCourtroom.a:  draw_functions.o animations.o camera.o script_read.o keyboard.o
	ar r $@ $^
	
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	$(RM) *.o *~ courtroom

distclean:
	$(RM) $(LIBS) *.o *~ courtroom

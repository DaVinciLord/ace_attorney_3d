CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror `sdl2-config --cflags` -D_XOPEN_SOURCE=700 -pthread
LDLIBS = -lGLU -lGL `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -pthread -lm 
LIBS = libCourtroom.a

all: courtroom

courtroom: courtroom.c $(LIBS)
	gcc $(CFLAGS) $< $(LIBS) $(LDLIBS)  -o courtroom
	mv courtroom ../

libCourtroom.a:  draw_functions.o animations.o camera.o script_read.o keyboard.o
	ar r $@ $^ 
	
%.o: %.c
	$(CC) -lm  -c $(CFLAGS) $< -o $@
	
clean:
	$(RM) *.o *~
	$(RM) ../courtroom

distclean:
	$(RM) $(LIBS) *.o *~ 
	$(RM) ../courtroom

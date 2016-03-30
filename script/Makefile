CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror `python-config --cflags`
LDLIBS = `python-config --ldflags`

all: hello 

clean:
	$(RM) *.o *~ hello

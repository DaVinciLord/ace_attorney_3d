CC=gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror -Ilua-5.3.2/include/ -Llua-5.3.2/lib/ -llua
LDLIBS = -Ilua-5.3.2/include/ -Llua-5.3.2/lib/ -llua

all: testlua

testlua.o: testlua.c
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ -c $< 

clean:
	$(RM) *.o *~ courtroom scriptreading


cc -o hello hello.c -Wall -I/home/l3info/mettovin/Dropbox/computer_science/courses/l3info/semestre_6/infographie/tp/ace_attorney_3d/script/lua-5.3.2/include -c 
cc -o hello hello.c -Wall -I/home/l3info/mettovin/Dropbox/computer_science/courses/l3info/semestre_6/infographie/tp/ace_attorney_3d/script/lua-5.3.2/include -L./lua-5.3.2/lib -llua -lm -ldl


GCC = g++
CFLAGS =
LFLAGS =

OBJS = lex.yy.o main.o
TARGET = test

all: $(OBJS)
	$(GCC) $(OBJS) $(LFLAGS) -o $(TARGET)


lex.yy.o : lex.yy.c
	$(GCC) lex.yy.c -ll -c
lex.yy.c : lex.l
	flex lex.l
main.o : handle.h
.cpp.o:
	$(GCC) $(CFLAGS) -c $<

clean:
	rm -rf *.o $(TARGET) lex.yy.c

GCC = g++
CFLAGS = -g
LFLAGS =

OBJS = dbms.o main.o database.o table.o
TARGET = test

all: $(OBJS)
	$(GCC) $(OBJS) $(LFLAGS) -o $(TARGET)

dbms.o : handle.h
main.o : handle.h
table.o : handle.h
database.o : handle.h


.cpp.o:
	$(GCC) $(CFLAGS) -c $<

clean:
	rm -rf *.o $(TARGET) lex.yy.c

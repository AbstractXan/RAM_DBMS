GCC = g++
CFLAGS =
LFLAGS =

OBJS = dbms.o main.o
TARGET = test

all: $(OBJS)
	$(GCC) $(OBJS) $(LFLAGS) -o $(TARGET)

cs16b030_dbms.o : cs16b030_dbms.h
sample.o : cs16b030_dbms.h

.cpp.o:
	$(GCC) $(CFLAGS) -c $<

clean:
	rm -rf *.o $(TARGET)

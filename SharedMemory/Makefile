CC            = gcc
CFLAGS        = -O4 -Wall -I/usr/local/include
DEST          = /usr/local/bin
LDFLAGS       = -L/usr/local/lib
LIBS          = -lstdc++
OBJS          = main.o SharedMemory.o
PROGRAM       = SharedMemoryTest

all:            $(PROGRAM)

$(PROGRAM):     $(OBJS)
				$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

clean:;         rm -f *.o *~ $(PROGRAM)

install:        $(PROGRAM)
				install -s $(PROGRAM) $(DEST)
TARGET=vdastring
CC=g++
DEBUG=-g
OPT=-O0
WARN=-Wall
CCFLAGS=$(DEBUG) $(OPT) $(WARN)
LD=g++
OBJS= main.o vdastring.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) 

main.o: main.cpp
	$(CC) -c $(CCFLAGS) main.cpp -o main.o
 
vdastring.o: VDAString.cpp
	$(CC) -c $(CCFLAGS) VDAString.cpp  -o vdastring.o
 
clean:
	@rm -f *.o

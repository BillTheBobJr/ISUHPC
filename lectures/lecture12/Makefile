CC = gcc
FFLAGS = -Wall
LFFLAG =
OBJECTS = main.o \
Push.o \
Pop.o \
Peek.o \
GetStackSize.o \
DisplayStack.o \
PreformOperation.o \
Flush.o


.PHONY : clean help

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean :
	rm -f $(OBJECTS) main.exe
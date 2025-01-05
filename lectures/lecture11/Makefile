# $ISUHPC / lectures / lecture/ codes / linked_list / Makefile
CC = gcc
FFLAGS = -Wall
LFFLAG =
OBJECTS = main.o \
GetNumberOfNodes.o \
GenerateList.o \
Print.o \
GetKey.o \
SearchList.o \
DeleteList.o

.PHONY : clean help

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
		$(CC) $(FFLAGS) -c $<

clean :
	rm -f $(OBJECTS) main.exe
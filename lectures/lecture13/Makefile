CC = gcc
FFLAGS = -Wall -lm
LFFLAG =
OBJECTS = main.o \
matrix.o

.PHONY : clean

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe
	
%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean :
	rm -f $(OBJECTS) main.exe
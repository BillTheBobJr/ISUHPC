CC = gcc
FFLAGS = -Wall -lm
LFFLAG =
OBJECTS = FindZero.o \
GetShift.o \
Hessenberg.o \
QRA.o \
QRdecomp.o \
trimatrix.o \
matrix.o \
main.o

.PHONY : clean

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe
	
%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean :
	rm -f $(OBJECTS) main.exe
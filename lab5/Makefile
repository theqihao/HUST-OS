CC = g++
#CFLAGS = -O -Wall -g
CFLAGS = -O -w -g
OBJ = main.o myfile.o

qihao: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o qihao

myfile.o: myfile.h

main.o: myfile.h



#clean
.PHONY : clean
clean: 
	-rm -f *.o *~ qihao

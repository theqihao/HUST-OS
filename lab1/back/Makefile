CC = gcc
#CFLAGS = -O -Wall -g
CFLAGS = -O -w -g
OBJ = main.o head.o

qihao: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o qihao 

main.o: head.h

head.o: head.h

#clean
.PHONY : clean
clean: 
	-rm -f *.o *~ qihao

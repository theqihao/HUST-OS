CC = g++
#CFLAGS = -O -Wall -g
CFLAGS = -O -w -g
OBJ =  main.o

qihao: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o qihao 


main.o: myfile.h

#clean
.PHONY : clean
clean: 
	-rm -f *.o *~ qihao 

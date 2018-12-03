
LDFLAGS=-pthread

ObjectDir = ./src
.PHONY: clean all
#Built = built/main.o built/producer.o built/cosumer.o

#%.o: $(ObjectDir)/%.c produce.h
#	$(CC) -c $< -o built/$@
main.o :  src/cosumer.c  src/producer.c  src/main.c src/produce.h 
	gcc -c  src/cosumer.c  -o built/cosumer.o $(LDFLAGS)
#producer.o : src/producer.c src/produce.h 
	gcc -c  src/producer.c -o built/producer.o $(LDFLAGS)
#main.o : src/main.c src/produce.h 
	gcc -c   src/main.c -o built/main.o $(LDFLAGS)  
#myapp: built/main.o built/producer.o built/cosumer.o
	$(CC) built/main.o built/producer.o built/cosumer.o -o built/myapp $(LDFLAGS)    
 
clean:
	rm -f *.o *~ myapp 

all: projetblockchain

projetblockchain : main.o blockchain.o
	gcc main.o blockchain.o -o projetblockchain -lssl -lcrypto


main.o : main.c blockchain.h
	gcc -c main.c

blockchain.o : blockchain.c blockchain.h
	gcc -c blockchain.c

clean :
	rm -f *.o core

mrproper : clean
	rm -f projetblockchain

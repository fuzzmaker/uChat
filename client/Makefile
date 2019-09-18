
clientSh: ../base/config.h client.o config.o interface.o login.o registion.o \
	recvMsg.o enterChat.o
	gcc -g -o clientSh client.o config.o interface.o login.o registion.o \
		recvMsg.o enterChat.o -lpthread

client.o: client.c ../base/config.h config.o
	gcc -g -c client.c

enterChat.o: enterChat.c ../base/config.h config.o
	gcc -g -c enterChat.c

login.o: login.c ../base/config.h config.o
	gcc -g -c login.c

registion.o: registion.c ../base/config.h config.o
	gcc -g -c registion.c

interface.o: interface.c ../base/config.h config.o
	gcc -g -c interface.c

recvMsg.o: recvMsg.c ../base/config.h config.o
	gcc -g -c recvMsg.c

config.o: ../base/config.c ../base/config.h
	gcc -g -c ../base/config.c

clean:
	rm client.o interface.o login.o registion.o \
     		recvMsg.o enterChat.o config.o

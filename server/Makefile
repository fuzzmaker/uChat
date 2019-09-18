

serverSh: ../base/config.h server.o config.o dbservice.o login_s.o registion_s.o \
	requestHandler.o privChat.o groupChat.o listUsers.o logout_s.o linked.o
	gcc -g -o serverSh server.o config.o dbservice.o login_s.o registion_s.o \
		requestHandler.o privChat.o groupChat.o listUsers.o logout_s.o linked.o -lpthread -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient

server.o: server.c ../base/config.h config.o
	gcc -g -c server.c

dbservice.o: dbservice.c ../base/config.h config.o
	gcc -g -c dbservice.c

login_s.o: login_s.c ../base/config.h config.o
	gcc -g -c login_s.c

registion_s.o: registion_s.c ../base/config.h config.o
	gcc -g -c registion_s.c

requestHandler.o: requestHandler.c ../base/config.h config.o
	gcc -g -c requestHandler.c

privChat.o: privChat.c ../base/config.h config.o
	gcc -g -c privChat.c

groupChat.o: groupChat.c ../base/config.h config.o
	gcc -g -c groupChat.c

listUsers.o: listUsers.c ../base/config.h config.o
	gcc -g -c listUsers.c

logout_s.o: logout_s.c ../base/config.h config.o
	gcc -g -c logout_s.c

linked.o: ../base/linked.c ../base/linked.h
	gcc -g -c ../base/linked.c

config.o: ../base/config.c ../base/config.h
	gcc -g -c ../base/config.c

clean:
	rm server.o dbservice.o login_s.o registion_s.o \
		requestHandler.o privChat.o groupChat.o listUsers.o logout_s.o linked.o 

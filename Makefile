
serverSh: server.o config.o dbservice.o login_s.o registion_s.o \
	requestHandler.o privChat.o groupChat.o listUsers.o logout_s.o
	gcc -o serverSh server.o config.o dbservice.o login_s.o registion_s.o \
		requestHandler.o privChat.o groupChat.o listUsers.o logout_s.o 

server.o: server/server.c base/config.h config.o
	gcc -c server/server.c

dbservice.o: server/dbservice.c base/config.h config.o
	gcc -c server/dbservice.c

login_s.o: server/login_s.c base/config.h config.o
	gcc -c server/login_s.c

registion_s.o: server/registion_s.c base/config.h config.o
	gcc -c server/registion_s.c

requestHandler.o: server/requestHandler.c base/config.h config.o
	gcc -c server/requestHandler.c

privChat.o: server/privChat.c base/config.h config.o
	gcc -c server/privChat.c

groupChat.o: server/groupChat.c base/config.h config.o
	gcc -c server/groupChat.c

listUsers.o: server/listUsers.c base/config.h config.o
	gcc -c server/listUsers.c

logout.o: server/logout.c base/config.h config.o
	gcc -c server/logout.c

config.o: base/config.c base/config.h
	gcc -c base/config.c

clean:
	rm server.o config.o dbservice.o login_s.o registion_s.o \
		requestHandler.o privChat.o groupChat.o listUsers.o logout_s.o

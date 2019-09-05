#include "config.h"

void requestHandler(int fd){
	Message msg;
	char buf[MAX_BUFSIZE];
	memset(&msg,0,sizeof(msg));
	int len=recv(fd,buf,MAX_BUFSIZE);
	if(len<=0) return;
	memcpy(&msg,buf,MAX_BUFSIZE);
	switch(msg.msgType){
		case LOGIN:
			login(&msg,fd);
			break;
		case REGISTION:
			registion(&msg,fd);
			break;
		case GROUPCHAT:
			groupChat(&msg,fd);
			break;
		case PRIVCHAT:
			privChat(&msg,fd);
			break;
		case LISTUSERS:
			listUsers(&msg,fd);
			break;
		case HISTRECORDS:
			hisRecords(&msg,fd);
			break;
		case UNKNOWN:
			fprintf(stderr,"unknown request msg type");
			break;
	}
	
}

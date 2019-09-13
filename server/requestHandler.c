#include "../base/config.h"

void requestHandler(int fd){
	Message msg;
	char buf[MAX_BUFSIZE];
	memset(&msg,0,sizeof(msg));
	int len=recv(fd,buf,MAX_BUFSIZE,0);
	if(len<=0) return;
	memcpy(&msg,buf,MAX_BUFSIZE);
	switch(msg.msgType){
		case LOGIN:
			login_s(&msg,fd);
			break;
		case REGIST:
			registion_s(&msg,fd);
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
			//histRecords(&msg,fd);
			break;
		case LOGOUT:
			logout_s(&msg,fd);
		case UNKNOWN:
			fprintf(stderr,"unknown request msg type");
			break;
	}
	
}

#include "../base/config.h"

void requestHandler(void *arg){
	sData data=*(sData *)arg;
	printf("requestHandler fd:%d\n",data.fd);
	int fd=data.fd;
	Message msg;
	char buf[MAX_BUFSIZE];
	memset(&msg,0,sizeof(msg));
	int len=recv(fd,buf,MAX_BUFSIZE,0);
	printf("recv len:%d\n",len);
	if(len<=0){
		rmClient(fd,1);
		return;
	}
	memcpy(&msg,buf,len);
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
			break;
		case UNKNOWN:
			printf("unknown request msg type");
			break;
	}
	
}

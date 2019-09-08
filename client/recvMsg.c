#include "config.h"

void recvMsg(int fd){
	Message msg;
	char buf[MAX_BUFSIZE];
	while(1){
		memset(&msg,0,sizeof(msg));
		memset(buf,0,sizeof(buf));
		int len=recv(fd,buf,sizeof(buf),0);
		if(len>0){
			memcpy(&msg,buf,len);
			switch(msg.msgType){
				case PRIVCHAT:
					printf("private chat:\n");
					printf("%s: %s\n",msg.sendName,msg.content);
					break;
				case GROUPCHAT:
					printf("group chat:\n");
					printf("%s: %s\n",msg.sendName,msg.content);
					break;
				case LISTUSERS:
					printf("online user list:\n");
					printf("%s\n",msg.content);
					break;
				default:
					break;
			}
		}
	}
	_exit(0);
}


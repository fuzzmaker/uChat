#include "../base/config.h"

void recvMsg(int *fd){
	Message msg;
	char buf[MAX_BUFSIZE];
	while(1){
		memset(&msg,0,sizeof(msg));
		memset(buf,0,sizeof(buf));
		int len=recv(*fd,buf,sizeof(buf),0);
		if(len>0){
			memcpy(&msg,buf,len);
			switch(msg.msgType){
				case PRIVCHAT:
					if(msg.state==NOT_ONLINE){
						printf("对方不在线\n");
					}else{
						printf("%s: %s\n",msg.sendName,msg.content);
					}
					break;
				case GROUPCHAT:
					printf("%s: %s\n",msg.sendName,msg.content);
					break;
				case LISTUSERS:
					printf("online user list:\n");
					listUsers_c(&msg);
					break;
				default:
					break;
			}
		}
	}
	_exit(0);
}

void listUsers_c(Message *msg){
	char delim[]=",";
	char *uname=strtok(msg->content,delim);
	while(uname!=NULL){
		printf("%s\n",uname);
		uname=strtok(NULL,delim);
	}
}

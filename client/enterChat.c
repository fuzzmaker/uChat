#include "config.h"

void enterChat(int fd){
	char buf[MAX_BUFSIZE];
	int choice;
	Message msg;
	memset(&msg,0,sizeof(msg));
	memset(buf,0,MAX_BUFSIZE);
	helpInterface();
	setbuf(stdin,NULL);
	scanf("%d",&choice);
	switch(choice){
		case GROUPCHAT:
			msg.msgType=GROUPCHAT;
			msg.content="";
			memcpy(buf,&msg,sizeof(msg));
			send(fd,buf,sizeof(buf));
			groupChat(fd);
			break;
		case PRIVATECHAT:
			msg.msgType=PRIVATECHAT;
			msg.content="";
			memcpy(buf,&msg,sizeof(msg));
			send(fd,buf,sizeof(buf));
			privateChat(fd);
			break;
		case LISTUSERS:
			msg.msgType=LISTUSERS;
			msg.content="";
			memcpy(buf,&msg,sizeof(msg));
			send(fd,buf,sizeof(buf));
			listUsers(fd);
			break;
		case EXIT:
			close(fd);
			break;
		default :
			puts("unknow type\n");
			enterChat(fd);
			break;
	}
	_exit(0);		
}

#include "config.h"

void privChat(Message *msg,int fd){
	Node *cursor=userList->head;
	char buf[MAX_BUFSIZE];
	User *user;
	int tofd=-1;
	memset(buf,0,sizeof(buf))
	while(cursor!=NULL){
		user=(User *)(cursor->val);
		if(strcmp(user->name,msg->recvName)==0){
			fd=user->fd;
			break;
		}
		cursor=cursor->next;
	}
	if(tofd<0){
		memset(&msg,0,sizeof(msg));
		msg.msgType=RESULT;
		msg.state=FAIL;
		strcpy(msg.content,"对方不在线");
		send(fd,buf,sizeof(buf),0);
		_exit(0);
	}
	memcpy(buf,&msg,sizeof(msg));
	send(tofd,buf,sizeof(buf),0);
	_exit(0);
	
}

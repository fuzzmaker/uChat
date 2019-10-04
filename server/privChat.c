#include "../base/config.h"
extern Linked *userList;

void privChat(Message *msg,int fd){
	printf("进入私聊...\n");
	Message sendMsg;
	Node *cursor=userList->head;
	char buf[MAX_BUFSIZE];
	User *user;
	int tofd=-1;
	memset(buf,0,sizeof(buf));
	memset(&sendMsg,0,sizeof(Message));
	while(cursor!=NULL){
		user=(User *)(cursor->val);
		if(strcmp(user->name,msg->recvName)==0){
			tofd=user->fd;
			break;
		}
		cursor=cursor->next;
	}
	if(tofd<0){
		sendMsg.msgType=PRIVCHAT;
		sendMsg.state=NOT_ONLINE;
		strcpy(sendMsg.content,"对方不在线");
		memcpy(buf,&sendMsg,sizeof(Message));
		send(fd,buf,sizeof(buf),0);
		return;
	}
	memcpy(buf,msg,sizeof(Message));
	send(tofd,buf,sizeof(buf),0);
	return;
	
}

#include "config.h"

void groupChat(Message *msg,int fd){
	User *user;
	char buf[MAX_BUFSIZE];
	Node *cursor=userList->head;
	while(cursor!=NULL){
		user=(User *)(cursor->val);
		if(user==NULL) continue;
		memset(buf,0,sizeof(buf));
		memcpy(buf,&msg,sizeof(msg));
		send(user->fd,buf,sizeof(buf),0);
		cursor=cursor->next;
	}
	_exit(0);
}

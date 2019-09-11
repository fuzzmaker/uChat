#include "../base/config.h"

void listUsers(int fd){
	Message msg;
	User *user;
	Node *temp=userList->head;
	char buf[MAX_BUFSIZE];
	char name[21];
	memset(buf,0,sizeof(buf));
	memset(&msg,0,sizeof(msg));
	while(temp!=NULL){
		user=(User *)(temp->val);
		strcpy(name,user->name);
		name[strlen(user->name)]=0;
		strcat(msg.content,name);
		strcat(msg.content,",");
		temp=temp->next;
	}
	msg.msgType=RESULT;
	msg.state=SUCCESS;
	memcpy(buf,&msg,sizeof(msg));
	send(fd,buf,sizeof(buf),0);
	_exit(0);
}

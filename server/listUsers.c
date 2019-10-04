#include "../base/config.h"
extern Linked *userList;

void listUsers(Message *msg,int fd){
	Message rectMsg;
	User *user;
	Node *temp=userList->head;
	char buf[MAX_BUFSIZE];
	char name[21];
	memset(buf,0,sizeof(buf));
	memset(&rectMsg,0,sizeof(rectMsg));
	while(temp!=NULL){
		memset(name,0,sizeof(name));
		user=(User *)(temp->val);
		strcpy(name,user->name);
		name[strlen(user->name)]=0;
		strcat(rectMsg.content,name);
		strcat(rectMsg.content,",");
		printf("next node %p\n",temp->next);
		temp=temp->next;
	}
	rectMsg.msgType=LISTUSERS;
	rectMsg.state=SUCCESS;
	memcpy(buf,&rectMsg,sizeof(rectMsg));
	send(fd,buf,sizeof(buf),0);
	return;
}

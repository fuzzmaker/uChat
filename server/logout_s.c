#include "../base/config.h"
extern Linked *userList;

int userCompare(void *u1,void *u2){
	User *user1=(User *)u1;
	User *user2=(User *)u2;
	return memcmp(user1->name,user2->name,MAX_NAME_LEN);
}

void logout_s(Message *msg,int fd){
	userList->compareTo=userCompare;
	User user;
	Message rectMsg;
	char buf[MAX_BUFSIZE];
	memset(&rectMsg,0,sizeof(rectMsg));
	memset(buf,0,sizeof(buf));
	strcpy(user.name,msg->sendName);
	userList->removeNode(userList,(void *)&user);
	rectMsg.msgType=RESULT;
	rectMsg.state=SUCCESS;
	strcpy(rectMsg.content,"登出成功");
	memcpy(buf,&rectMsg,sizeof(rectMsg));
	send(fd,buf,sizeof(buf),0);
	_exit(0);
		
}

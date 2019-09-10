#include "config.h"

int userCompare(void *u1,void *u2){
	User *user1=(User *)u1;
	User *user2=(User *)u2;
	return memcmp(user1->name,user->name);
}

void logout(Message *msg,int fd){
	userList->compareTo=userCompare;
	User user;
	Message msg;
	char buf[MAX_BUFSIZE];
	memset(&msg,0,sizeof(msg));
	memset(buf,0,sizeof(buf));
	strcpy(user.name,msg->sendName);
	userList->removeNode(userList,user);
	msg.msgType=RESULT;
	msg.state=SUCCESS;
	strcpy(msg.content,"登出成功");
	memcpy(buf,&msg,sizeof(msg));
	send(fd,buf,sizeof(buf),0);
	_exit(0);
		
}

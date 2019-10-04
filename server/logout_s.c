#include "../base/config.h"

void logout_s(Message *msg,int fd){
	User user;
	Message rectMsg;
	char buf[MAX_BUFSIZE];
	memset(&rectMsg,0,sizeof(rectMsg));
	memset(buf,0,sizeof(buf));
	strcpy(user.name,msg->sendName);
	rectMsg.msgType=LOGOUT;
	rectMsg.state=SUCCESS;
	strcpy(rectMsg.content,"登出成功");
	memcpy(buf,&rectMsg,sizeof(rectMsg));
	send(fd,buf,sizeof(buf),0);
	rmClient(fd,1);
	return;
		
}

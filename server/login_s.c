#include "../base/config.h"

extern Linked *userList;

void login_s(Message *msg,int fd){
	Message reMsg;
	char buf[MAX_BUFSIZE];
	char delims[]=",";
	char *name,*passwd;
	memset(buf,0,MAX_BUFSIZE);
	name=strtok(msg->content,delims);
	passwd=strtok(NULL,delims);
	User *oUser=getUserByName(name);
	reMsg.msgType=RESULT;
	if(oUser==NULL){
		printf("用户不存在，请先注册\n");
		reMsg.state=UNREGIST;
		strcpy(reMsg.content,geterrmsg(reMsg.state));
		memcpy(buf,&reMsg,sizeof(reMsg));
		send(fd,buf,MAX_BUFSIZE,0);
		close(fd);
		_exit(0);
	}
	if(oUser->state==ALREADY_ONLINE){
		printf("用户已在线\n");
        	reMsg.state=ALREADY_ONLINE;
        	strcpy(reMsg.content,geterrmsg(reMsg.state));
        	memcpy(buf,&reMsg,sizeof(reMsg));
        	send(fd,buf,MAX_BUFSIZE,0);
        	close(fd);
		_exit(0);                           
	 }
	if(strcmp(oUser->passwd,passwd)!=0){
		printf("密码错误\n");
		reMsg.state=WRONGPWD;             
		strcpy(reMsg.content,geterrmsg(reMsg.state));
		memcpy(buf,&reMsg,sizeof(reMsg));
       		send(fd,buf,MAX_BUFSIZE,0);
        	close(fd);
        	_exit(0);
	}
	//将user信息加入在线用户列表
	oUser->fd=fd;
	userList->insertNode(userList,(void *)oUser);
	//回复客户端
	reMsg.state=SUCCESS;             
	strcpy(reMsg.content,geterrmsg(reMsg.state));
	memcpy(buf,&reMsg,sizeof(reMsg));
       	send(fd,buf,MAX_BUFSIZE,0);
        _exit(0);

}

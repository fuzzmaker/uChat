#include "../base/config.h"

void login_s(Message *msg,int fd){
	Message reMsg;
	char buf[MAX_BUFSIZE];
	char delims[]=",";
	char *name,*passwd;
	memset(buf,0,MAX_BUFSIZE);
	name=strtok(msg.content,delims);
	passwd=strtok(NULL,delims);
	User *oUser=getUserByName(name);
	reMsg.msgType=RESULT;
	if(oUser==NULL){
		reMsg.state=UNREGISTION;
		strcpy(reMsg.content,geterrmsg(reMsg.state));
		memcpy(buf,&reMsg,sizeof(reMsg));
		send(fd,buf,MAX_BUFSIZE,0);
		close(fd);
		_exit(0);
	}
	if(oUser->state==ALREADY_ONLINE){
        	reMsg.state=ALREADY_ONLINE;
        	strcpy(reMsg.content,geterrmsg(reMsg.state));
        	memcpy(buf,&reMsg,sizeof(reMsg));
        	send(fd,buf,MAX_BUFSIZE,0);
        	close(fd);
		_exit(0);                           
	 }
	if(strcmp(oUser->passwd,passwd)!=0){
		reMsg.state=WRONGPASSWD;             
		strcpy(reMsg.content,geterrmsg(reMsg.state));
		memcpy(buf,&reMsg,sizeof(reMsg));
       		send(fd,buf,MAX_BUFSIZE,0);
        	close(fd);
        	_exit(0);
	}
	//将user信息加入在线用户列表
	oUser->fd=fd;
	userList->insertNode(userList,oUser);
	//回复客户端
	reMsg.state=SUCCESS;             
	strcpy(reMsg.content,geterrmsg(reMsg.state));
	memcpy(buf,&reMsg,sizeof(reMsg));
       	send(fd,buf,MAX_BUFSIZE,0);
        _exit(0);

}

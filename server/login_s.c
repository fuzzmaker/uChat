#include "config.h"

void login(Message *msg,int fd){
	Message reMsg;
	char buf[MAX_BUFSIZE];
	char delims[]=",";
	char *name,*passwd;
	memset(buf,0,MAX_BUFSIZE);
	name=strtok(msg.content,delims);
	passwd=strtok(NULL,delims);
	User *oUser=getUserByName(name);
	if(oUser==NULL){
		reMsg.msgType=LOGIN;
		reMsg.state=UNREGISTION;
		reMsg.content=geterrmsg(reMsg.state);
		memcpy(buf,&reMsg,sizeof(reMsg));
		send(fd,buf,MAX_BUFSIZE);
		close(fd);
		_exit(0);
	}
	if(oUser->state==ALREADY_ONLINE){
		reMsg.msgType=LOGIN;                 	
        	reMsg.state=ALREADY_ONLINE;
        	reMsg.content=geterrmsg(reMsg.state);
        	memcpy(buf,&reMsg,sizeof(reMsg));
        	send(fd,buf,MAX_BUFSIZE);
        	close(fd);
		_exit(0);                           
	 }
	if(strcmp(oUser->passwd,passwd)!=0){
		reMsg.msgType=LOGIN;                 	
		reMsg.state=WRONGPASSWD;             
		reMsg.content=geterrmsg(reMsg.state);
		memcpy(buf,&reMsg,sizeof(reMsg));
       		send(fd,buf,MAX_BUFSIZE);
        	close(fd);
        	_exit(0);
	}
	//将user信息加入在线用户列表
	oUser->fd=fd;
	add(user_list,oUser);	
	//回复客户端
	reMsg.msgType=LOGIN;                 	
	reMsg.state=SUCCESS;             
	reMsg.content=geterrmsg(reMsg.state);
	memcpy(buf,&reMsg,sizeof(reMsg));
       	send(fd,buf,MAX_BUFSIZE);
        _exit(0);

}

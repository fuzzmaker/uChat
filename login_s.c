#include "config.h"

void login(Message msg,int fd){
	Message reMsg;
	User user;
	char buf[MAX_BUFSIZE];
	memset(buf,0,MAX_BUFSIZE);
	memset(&user,0,sizeof(user));
	int len;
	len=recv(fd,buf,MAX_BUFSIZE,0);
	if(len<=0){
		puts("登录失败\n");
		_exit(0);
	}
	memcpy(&user,buf,len);
	User *oUser=getUserByName(user.name);
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
	if(strcmp(oUser->passwd,user.passwd)!=0){
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
        close(fd);
        _exit(0);

}

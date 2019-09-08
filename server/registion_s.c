#include "config.h"

void registion(Message *msg,int fd){
	Message reMsg;
	User *user;
	char buf[MAX_BUFSIZE];
	char *name,*passwd;
	char delims[]=",";
	memset(&reMsg,0,sizeof(reMsg));
	memset(buf,0,MAX_BUFSIZE);
	name=strtok(msg->content,delims);
	passwd=strtok(NULL,delims);
	reMsg.msgType=RESULT;
	if(name==NULL || strlen(name)==0){
		reMsg.state=FAIL;
		strcpy(reMsg.content,"用户名不能为空");
		memcpy(buf,&reMsg,sizeof(reMsg));
		send(fd,buf,MAX_BUFSIZE);
		_exit(1);
	}
	if(passwd==NULL || strlen(passwd)==0){
		reMsg.state=FAIL;
		strcpy(reMsg.content,"密码不能为空");
		memcpy(buf,&reMsg,sizeof(reMsg));
		send(fd,buf,MAX_BUFSIZE);
		_exit(1);
	}
	user=getUserByName(name);
	if(user!=NULL){
		reMsg.state=DUPLICA_NAME;
		strcpy(reMsg.content,"用户名已存在");
		memcpy(buf,&reMsg,sizeof(reMsg));
		sned(fd,buf,MAX_BUFSIZE);
		_exit(1);	
	}
	//保存用户
	memset(user,0,sizeof(user));
	strcpy(user->name,name);
	strcpy(user->passwd,passwd);
	user.state=NO;
	addUser(user);
	reMsg.state=SUCCESS;
	strcpy(reMsg.content,"注册成功,请前往登录");
	memcpy(buf,&reMsg,sizeof(reMsg));
	send(fd,buf,MAX_SIZEBUF);
	_exit(0);

}

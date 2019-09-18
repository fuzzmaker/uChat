#include "../base/config.h"

void registion_s(Message *msg,int fd){
	printf("进入注册流程\n");
	Message reMsg;
	User *user,nUser;
	char buf[MAX_BUFSIZE];
	char *name,*passwd;
	char delims[]=",";
	memset(&reMsg,0,sizeof(reMsg));
	memset(buf,0,MAX_BUFSIZE);
	name=strtok(msg->content,delims);
	passwd=strtok(NULL,delims);
	reMsg.msgType=RESULT;
	if(name==NULL || strlen(name)==0){
		printf("用户名不能为空\n");
		reMsg.state=FAIL;
		strcpy(reMsg.content,"用户名不能为空");
		memcpy(buf,&reMsg,sizeof(reMsg));
		send(fd,buf,MAX_BUFSIZE,0);
		close(fd);
		return;
	}
	if(passwd==NULL || strlen(passwd)==0){
		printf("密码不能为空\n");
		reMsg.state=FAIL;
		strcpy(reMsg.content,"密码不能为空");
		memcpy(buf,&reMsg,sizeof(reMsg));
		send(fd,buf,MAX_BUFSIZE,0);
		close(fd);
		return;
	}
	printf("user name:%s\n",name);
	user=getUserByName(name);
	if(user!=NULL){
		printf("用户名已存在\n");
		reMsg.state=DUPLICATE_NAME;
		strcpy(reMsg.content,"用户名已存在");
		memcpy(buf,&reMsg,sizeof(reMsg));
		send(fd,buf,MAX_BUFSIZE,0);
		close(fd);
		return;	
	}
	printf("保存用户信息\n");
	//保存用户
	strcpy(nUser.name,name);
	strcpy(nUser.passwd,passwd);
	nUser.state=NO;
	int id=addUser(nUser);
	if(id<=0){
		reMsg.state=FAIL;
		printf("注册失败\n");
		strcpy(reMsg.content,"注册失败");
	}else{
		reMsg.state=SUCCESS;
		printf("注册成功\n");
		strcpy(reMsg.content,"注册成功,请前往登录");
	}
	memcpy(buf,&reMsg,sizeof(reMsg));
	send(fd,buf,MAX_BUFSIZE,0);
	close(fd);
	return;

}

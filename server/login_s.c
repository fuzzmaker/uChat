#include "../base/config.h"

extern Linked *userList;

void login_s(Message *msg,int fd){
	printf("进入登录流程...\n");
	Message reMsg;
	char buf[MAX_BUFSIZE];
	char delims[]=",";
	char *name,*passwd;
	int retry=3;//消息重发次数
	memset(buf,0,MAX_BUFSIZE);
	memset(&reMsg,0,sizeof(Message));
	name=strtok(msg->content,delims);
	printf("name:%s\n",name);
	passwd=strtok(NULL,delims);
	printf("passwd:%s\n",passwd);
	User *oUser=getUserByName(name);
	reMsg.msgType=RESULT;
	if(oUser==NULL){
		printf("用户不存在，请先注册\n");
		reMsg.state=UNREGIST;
		strcpy(reMsg.content,geterrmsg(reMsg.state));
		memcpy(buf,&reMsg,sizeof(reMsg));
		send(fd,buf,MAX_BUFSIZE,0);
		rmClient(fd,0);
		return;
	}
	if(oUser->state==ALREADY_ONLINE){
		printf("用户已在线\n");
        	reMsg.state=ALREADY_ONLINE;
        	strcpy(reMsg.content,geterrmsg(reMsg.state));
        	memcpy(buf,&reMsg,sizeof(reMsg));
        	send(fd,buf,MAX_BUFSIZE,0);
        	rmClient(fd,0);
		return;                           
	 }
	if(strcmp(oUser->passwd,passwd)!=0){
		printf("密码错误\n");
		reMsg.state=WRONGPWD;             
		strcpy(reMsg.content,geterrmsg(reMsg.state));
		memcpy(buf,&reMsg,sizeof(reMsg));
       		send(fd,buf,MAX_BUFSIZE,0);
		rmClient(fd,0);
        	return;
	}
	//将user信息加入在线用户列表
	oUser->fd=fd;
	userList->insertNode(userList,oUser);
	//回复客户端
	reMsg.state=SUCCESS;             
	strcpy(reMsg.content,geterrmsg(reMsg.state));
	memcpy(buf,&reMsg,sizeof(reMsg));
       	send(fd,buf,sizeof(reMsg),0);
        return;

}

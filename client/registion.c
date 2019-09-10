#include "config.h"

#define MAX_NAME_LEN 20

void registion(int fd){
	Messgae msg;
	char buf[MAX_BUFSIZE];
	char name[MAX_NAME_LEN+1];
	char passwd[MAX_NAME_LEN+1];
	memset(&msg,0,sizeof(msg));
	printf("请输入用户名:\n");
	scanf("%s",name);
	while(strlen(name)>MAX_NAME_LEN){
		memset(name,0,sizeof(name));
		printf("用户名长度不超过20个字符,请重新输入:\n");
		scanf("%s",name);
	}
	printf("请输入密码:\n");
	scanf("%s",passwd);
	while(strlen(passwd)>MAX_NAME_LEN){
		memset(passwd,0,sizeof(passwd));
		printf("密码长度不超过20个字符,请重新输入:\n");
		scanf("%s",passwd);
	}
	strcat(msg.content,name);
	strcat(msg.content,",");
	strcat(msg.content,passwd);
	msg.msgType=REGIST;
	memcpy(buf,&msg,sizeof(msg));
	send(fd,buf,MAX_BUFSIZE,0);
	memset(buf,0,MAX_BUFSIZE);
	int len;
	if((len=recv(fd,buf,MAX_BUFSIZE,0))<=0){
		printf("注册失败\n");
		close(fd);
		_exit(1);
	}
	memset(&msg,0,sizeof(msg));
	memcpy(&msg,buf,len);
	if(msg.magType==RESULT && msg.state=SUCCESS){
		printf("注册成功\n");
		printf("=================================\n");
	}else{
		printf("注册失败:\n");
		printf("%s\n",msg.content);
		printf("=================================\n");
	}
	close(fd);
	_exit(0);

}

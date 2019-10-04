#include "../base/config.h"

void login(int fd){
	Message msg;
	User user;
	char buf[MAX_BUFSIZE];
	memset(buf,0,MAX_BUFSIZE);
	memset(&msg,0,sizeof(msg));
	puts("请输入用户名: ");
	setbuf(stdin,NULL);
	scanf("%s",user.name);
	puts("请输入密码: ");
	scanf("%s",user.passwd);
	msg.msgType=LOGIN;
	strcpy(msg.sendName,user.name);
	strcat(msg.content,user.name);
	strcat(msg.content,",");
	strcat(msg.content,user.passwd);
	memcpy(buf,&msg,sizeof(msg));
	//发送用户密码到服务端
	if(send(fd,buf,sizeof(buf),0)==-1){
		printf("发送登录请求失败\n");
		close(fd);
		return;
	}
	memset(buf,0,MAX_BUFSIZE);
	//接收服务端消息
	int len=recv(fd,buf,MAX_BUFSIZE,0);
	if(len<=0){
		puts("登录失败,连接异常\n");
		close(fd);
		_exit(1);
	}
	memset(&msg,0,sizeof(msg));
	memcpy(&msg,buf,len);
	switch (msg.state){
		case FAIL:
			puts(msg.content);
			break;
		case SUCCESS:
			puts(msg.content);
			//进入聊天室
			enterChat(&user,fd);
			break;
		case UNREGIST:
			puts(msg.content);
			break;
		default:
			puts("unknow state\n");
			break;
	}
	close(fd);
	//_exit(0);
	return;
	
}

#include "../base/config.h"

void login(int fd){
	Message msg;
	User user;
	char buf[MAX_BUFSIZE];
	memset(buf,0,MAX_BUFSIZE);
	memset(&msg,0,sizeof(msg));
	puts("请输入用户名\n");
	setbuf(stdin,NULL);
	scanf("%s",user.name);
	puts("请输入密码\n");
	scanf("%s",user.passwd);
	memcpy(buf,&user,sizeof(user));
	//发送用户密码到服务端
	send(fd,buf,strlen(buf),0);
	memset(buf,0,MAX_BUFSIZE);
	//接收服务端消息
	int len=recv(fd,buf,MAX_BUFSIZE,0);
	if(len<0){
		puts("登录失败,连接异常\n");
		close(fd);
		_exit(0);
	}
	memcpy(msg,buf,len);
	switch (msg.state){
		case FAIL:
			puts(msg.content);
			break;
		case SUCCESS:
			puts("登录成功!");
			//进入聊天室
			enterChat(&user,fd);
			break;
		default:
			puts("unknow state");
			break;
	}
	close(fd);
	_exit(0);
	
}

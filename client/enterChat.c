#include "../base/config.h"

void enterChat(User *user,int fd){
	char buf[MAX_BUFSIZE];
	char msgbuf[MAX_MSGSIZE];
	char recvName[20];
	int choice;
	pthread_t pid;
	Message msg;
	pthread_create(&pid,NULL,(void *)recvMsg,&fd);
	if(pid==-1){
		printf("create recvMsg thread error\n");
		close(fd);
		_exit(1);
	}
	while(1){	
		choice=-1;
		memset(&msg,0,sizeof(msg));
		memset(buf,0,MAX_BUFSIZE);
		chatTypeInterface();
		setbuf(stdin,NULL);
		scanf("%d",&choice);
		switch(choice){
			case 1://群聊
				while(1){
					memset(&msg,0,sizeof(msg));
					memset(buf,0,sizeof(buf));
					memset(msgbuf,0,sizeof(msgbuf));
					msg.msgType=GROUPCHAT;
					strcpy(msg.sendName,user->name);
					printf("消息输入:\n");
					scanf("%s",msgbuf);
					if(memcmp(msgbuf,"quit",3)==0){
						break;
					}
					strcpy(msg.content,msgbuf);
					memcpy(buf,&msg,sizeof(msg));
					send(fd,buf,sizeof(buf),0);
				}
				break;
			case 2://私聊
				while(1){
					memset(&msg,0,sizeof(msg));
					memset(buf,0,sizeof(buf));
					memset(msgbuf,0,sizeof(msgbuf));
					msg.msgType=PRIVCHAT;
					strcpy(msg.sendName,user->name);
					printf("请输入私聊对象名称:\n");
					scanf("%s",recvName);
					strcpy(msg.recvName,recvName);
					printf("请输入消息内容:\n");
					scanf("%s",msgbuf);
					if(memcmp(msgbuf,"quit",4)==0){
						break;
					}
					strcpy(msg.content,msgbuf);
					memcpy(buf,&msg,sizeof(msg));
					send(fd,buf,sizeof(buf),0);
				}
				break;
			case 3://查看在线用户
				msg.msgType=LISTUSERS;
				strcpy(msg.content,"");
				memcpy(buf,&msg,sizeof(msg));
				send(fd,buf,sizeof(buf),0);
				break;
			case 4://退出
				msg.msgType=LOGOUT;       	
                        	strcpy(msg.content,"");
                        	memcpy(buf,&msg,sizeof(msg));
                        	send(fd,buf,sizeof(buf),0);
				close(fd);
				_exit(0);
			default :
				puts("unknow type\n");
				break;
		}
	}
	_exit(0);		
}

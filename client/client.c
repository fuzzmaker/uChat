/******************************
 *
 * 客户端程序
 *
 *****************************/

#include "../base/config.h"


int main(void){
	Mssage msg;
	int type;
	char buf[BUF_MAXSIZE];
	struct sockaddr_in sv_ddr;
	int addr_len=sizeof(sv_addr);
	memset(&sv_addr,0,addr_len);
	memset(&cli_addr,0,addr_len);
	sv_addr.sin_family=AF_INET;
	sv_addr.sin_addr.s_addr=inet_addr(SERVER_IP);
	sv_addr.sin_port=htons(SERVER_PORT);
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		puts("create client socket error\n");
		_exit(EXIT_FAILURE);
	}
	while(1){//循环是为了能切换type	
		int clifd=connect(sockfd,(struct sockaddr *)&sv_addr,addr_len);
		if(clifd==-1){
			puts("connect to server error\n");
			_exit(EXIT_FAILURE);
		}
		mainInterface();
		setbuf(stdin,NULL);
		scanf("%d",&type);
		memset(buf,0,BUF_MAXSIZE);
		memset(&msg,0,sizeof(msg));
		switch(type){
			case 1:
				msg.msgType=LOGIN;
				msg.sendaddr=sv_addr;
				msg.content="";
				memcpy(buf,&msg,sizeof(msg));
				send(sockfd,buf,sizeof(buf),0);
				login(sockfd);
				break;
			case 2:
				msg.msgType=REGISTION;
				msg.sendaddr=sv_addr;
				msg.content="";
				memcpy(buf,&msg,sizeof(msg));
				send(sockfd,buf,sizeof(buf),0);
				registion(sockfd);
				break;
			case 3:
				close(sockfd);
				_exit(0);
				break;
			default:
				puts("unknow operation\n");
				break;
		}
	}
	close(sockfd);
}

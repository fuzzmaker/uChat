/******************************
 *
 * 客户端程序
 *
 *****************************/

#include "../base/config.h"


int main(void){
	Message msg;
	int type;
	char buf[MAX_BUFSIZE];
	struct sockaddr_in sv_addr;
	int addr_len=sizeof(sv_addr);
	memset(&sv_addr,0,addr_len);
        sv_addr.sin_family=AF_INET;
        sv_addr.sin_addr.s_addr=inet_addr(SERVER_IP);
        sv_addr.sin_port=htons(SERVER_PORT);
	int sockfd;	
	while(1){//循环是为了能切换type		
		sockfd=socket(AF_INET,SOCK_STREAM,0);
		if(sockfd==-1){
			puts("create client socket error\n");
			_exit(1);
		}
		int clifd=connect(sockfd,(struct sockaddr *)&sv_addr,addr_len);
		if(clifd==-1){
			puts("connect to server error\n");
			close(sockfd);
			_exit(1);
		}
		mainInterface();
		type=0;
		setbuf(stdin,NULL);
		scanf("%d",&type);
		memset(buf,0,MAX_BUFSIZE);
		memset(&msg,0,sizeof(msg));
		switch(type){
			case 1:
				login(sockfd);
				break;
			case 2:
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

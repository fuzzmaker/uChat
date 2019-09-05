#include "config.h"

Node *user_list=NULL;
fd_set fds;//read fds
int MAX_FDS=0;

int main(void){
	struct sockaddr_in saddr;
	struct timval timeout;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_addr=inet_addr(SERVER_IP);
	saddr.sin_port=htons(SERVER_PORT);
	int svfd=socket(AF_INET,SOCK_STREAM,0);
	if(svfd==-1){
		fprintf(stderr,"create server socket error\n");
		_exit(1);
	}	
	if(bind(svfd,(struct sockaddr *)&saddr,sizeof(saddr))==-1){
		fprintf(stderr,"bind server socket error\n");
		_exit(1);
	}
	listen(svfd,MAX_LISTEN_NUM);
	FD_ZERO(&fds);//清空描述符集
	FD_SET(svfd,&fds);
	MAX_FDS=fds+1;
	timeout.tv_sec=4;
	timeout.tv_usec=0;
	while(1){
		if(select(MX_FDS,&fds,NULL,NULL,&timeout)>0){
			if(FD_ISSET(svfd,&fds)){
				
			}
		}
	}
}

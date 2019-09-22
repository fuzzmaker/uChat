#include "../base/config.h"


Linked userList;
int cli_fds[MAX_LISTEN_NUM];
extern int errno;

int main(void){
	struct sockaddr_in s_addr,c_addr;
	struct timeval timeout;
	char buf[MAX_BUFSIZE];
	init_linked(&userList);
	Message msg;
	fd_set fdset,rect;
	int max_fd=-1;
	int socklen=sizeof(struct sockaddr_in);
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("create srever socket error\n");
		_exit(1);
	}
	memset(&s_addr,0,socklen);
	memset(&c_addr,0,socklen);
	s_addr.sin_family=AF_INET;
	s_addr.sin_addr.s_addr=inet_addr(SERVER_IP);
	s_addr.sin_port=htons(SERVER_PORT);
	if(bind(sockfd,(struct sockaddr *)&s_addr,socklen)==-1){
		printf("bind server addr error\n");
		_exit(1);
	}
	if(listen(sockfd,MAX_LISTEN_NUM)==-1){
		printf("server listen error\n");
		_exit(1);
	}
	for(int i=0;i<MAX_LISTEN_NUM;i++){
		cli_fds[i]=-1;
	}
	max_fd=sockfd;
	max_fd=sockfd>max_fd?sockfd:max_fd;
	timeout.tv_sec=4;
	timeout.tv_usec=0;
	while(1){
		FD_ZERO(&fdset);
		FD_SET(sockfd,&fdset);
		for(int i=0;i<=max_fd;i++){
			if(cli_fds[i]>0){
				FD_SET(i,&fdset);
			}
		}
		int readyNum=0;
		if((readyNum=select(max_fd+1,&fdset,NULL,NULL,&timeout))>0){
			if(FD_ISSET(sockfd,&fdset)){
				int fd=accept(sockfd,(struct sockaddr *)&c_addr,(socklen_t *)&socklen);
				int ofd=fd>max_fd?fd:max_fd;
				if(ofd>=MAX_LISTEN_NUM){
					printf("fail to connect,is too many connection...\n");
					memset(&msg,0,sizeof(msg));
					memset(buf,0,MAX_LISTEN_NUM);
					msg.msgType=RESULT;
					strcpy(msg.content,"连接已达上限,请稍后再试");
					msg.state=CONN_LIMIT;
					memcpy(buf,&msg,sizeof(msg));
					send(ofd,buf,sizeof(buf),0);

				}else{
					printf("接收到新的连接请求max_fd:%d\n",ofd);
					max_fd=ofd;
					FD_CLR(fd,&fdset);
					cli_fds[fd]=1;//1代表该位置设置了描述符
					if(readyNum--<=0) continue;
				}
				
			}
			for(int i=0;i<=max_fd;i++){
				if(cli_fds[i]>0&&FD_ISSET(i,&fdset)){
					struct tcp_info info;
					int slen=sizeof(info);
					if(getsockopt(i,IPPROTO_TCP,TCP_INFO,&info,(socklen_t *)&slen)==0){
						if(info.tcpi_state!=1){
							close(i);
							cli_fds[i]=-1;
							printf("client closed\n");
						}
					}
					pthread_t pid;
					pthread_create(&pid,NULL,(void *)requestHandler,&i);
					FD_CLR(i,&fdset);
					if(readyNum--<=0) break;
				}
			}
			
		}
	}
	close(sockfd);
	_exit(0);
}

#include "config.h"


Linked *userList=NULL;

int main(void){
	struct sockaddr_in s_addr,c_addr;
	struct timeval timeout;
	char buf[MAX_BUFSIZE];
	Message msg;
	fd_set fdset,rect;
	int max_fd=-1;
	int cli_fds[MAX_LISTEN_NUM]={0};
	int socklen=sizeof(struct sockaddr_in);
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		fprintf(stderr,"create srever socket error");
		_exit(1);
	}
	memset(&s_addr,0,socklen);
	memset(&c_addr,0,scoklen);
	s_addr.sin_family=AF_INET;
	s_addr.sin_addr.s_addr=inet_addr(SERVER_IP);
	s_addr.sin_port=htons(SERVER_PORT);
	if(bind(sockfd,(struct sockaddr *)&s_addr,socklen)==-1){
		fprintf(stderr,"bind server addr error");
		_exit(1);
	}
	if(listen(sockfd,MAX_LISTEN_NUM)==-1){
		fprintf(stderr,"server listen error ");
		_exit(1);
	}
	FD_ZERO(&fdset);
	FD_SET(sockfd,&fdset);
	MAX_FD=sockfd;
	max_fd=sockfd>max_fd?sockfd:max_fd;
	timeout.tv_sec=4;
	timeout.tv_usec=0;
	while(1){
		rect=fdset;
		int readyNum;
		if((readNum=select(max_fd+1,&rect,NULL,NULL,timeout))>0){
			if(FD_ISSET(sockfd,&rect)){
				int fd=accept(sockfd,(struct sockaddr *)&c_addr,socklen);
				int ofd=fd>max_fd?fd:max_fd;
				if(ofd>=MAX_LISETN_NUM){
					fprintf(stderr,"fail to connect,is too many connection...");
					memset(&msg,0,sizeof(msg));
					memset(buf,0,MAX_LISTEN_NUM);
					msg.msgType=RESULT;
					msg.content="连接已达上限,请稍后再试";
					msg.state=CONN_LIMIT;
					memcpy(buf,&msg,sizeof(msg));
					send(ofd,buf,sizeof(buf),0);

				}else{
					max_fd=ofd;
					FD_SET(fd,&fdset);
					cli_fds[fd]=1;//1代表该位置设置了描述符
					if(readyNum--<=0) continue;
				}
			}
			for(int i=0;i<=max_fd;i++){
				if(cli_fds[i]>0&&FD_ISSET(i,&rect)){
					pthread_t pid;
					pthread_create(&pid,NULL,(void *)requestHandler,&i);
					FD_CLR(i,&rect);
					if(readyNum--<=0) break;
				}
			}
		}
	}
	colse(sockfd);
	_exit(0);
}

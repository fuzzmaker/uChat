#include "../base/config.h"


Linked *userList;
int cli_fds[MAX_LISTEN_NUM];
pthread_mutex_t mutex;
static int max_fd;
extern int errno;

int main(void){
	struct sockaddr_in s_addr,c_addr;
	struct timeval timeout;
	char buf[MAX_BUFSIZE];
	userList=create_linked(&userCompare);
	pthread_mutex_init(&mutex,NULL);
	Message msg;
	fd_set fdset,rect;
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
	timeout.tv_sec=10;
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
				if(fd>=MAX_LISTEN_NUM){
					printf("连接失败,在线用户数已达上线...\n");
					memset(&msg,0,sizeof(msg));
					memset(buf,0,MAX_LISTEN_NUM);
					msg.msgType=RESULT;
					strcpy(msg.content,"连接已达上限,请稍后再试");
					msg.state=CONN_LIMIT;
					memcpy(buf,&msg,sizeof(msg));
					send(fd,buf,sizeof(buf),0);
					close(fd);
				}else{
					printf("接收到新的连接请求max_fd:%d\n",fd);
					updateMaxFD(fd);//更新当前最大fd
					FD_CLR(fd,&fdset);
					cli_fds[fd]=1;//1代表该位置设置了描述符
					if(readyNum--<=0) continue;
				}
				
			}
			for(int i=0;i<=max_fd;i++){
				if(cli_fds[i]>0&&FD_ISSET(i,&fdset)){
					printf("接收到fd:%d 消息\n",i);
					FD_CLR(i,&fdset);
					struct tcp_info info;
					int slen=sizeof(info);
					getsockopt(i,IPPROTO_TCP,TCP_INFO,&info,(socklen_t *)&slen);
					if(info.tcpi_state!=1){
						rmClient(i,1);
						printf("用户下线通知fd:%d\n",i);
					}else{
						pthread_t pid;
						sData data={i};
						pthread_create(&pid,NULL,(void *)requestHandler,&data);
						printf("创建线程fd:%d\n",i);
					}
					if(readyNum--<=0) break;
				}
			}
			
		}
	}
	close(sockfd);
	_exit(0);
}

int userCompare(void *u1,void *u2){
	if(u1==NULL || u2==NULL) return -1; 
	User *user1=(User *)u1;
	User *user2=(User *)u2;
	return (user1->fd)-(user2->fd);
}


void rmClient(int fd,int flag){
	pthread_mutex_lock(&mutex);
	cli_fds[fd]=-1;
	max_fd=max_fd==fd?max_fd--:max_fd;
	if(flag){
		User user={fd:fd};
		userList->removeNode(userList,&user);
	}
	pthread_mutex_unlock(&mutex);
	close(fd);
}

void updateMaxFD(int fd){
	pthread_mutex_lock(&mutex);
	max_fd=max_fd>fd?max_fd:fd;
	pthread_mutex_unlock(&mutex);
}

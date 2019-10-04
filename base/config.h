/**********************************
*
* 基本配置文件-包涵项目所需头文件
* 定义枚举类和用户链表结构体
* 
**********************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<linux/tcp.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/select.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<mysql/mysql.h>
#include<time.h>
#include "linked.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define MAX_LISTEN_NUM 20
#define MAX_NAME_LEN 20
#define DB_FILE "/var/db/chatuser"
#define MAX_BUFSIZE 8126
#define MAX_MSGSIZE 2048

#define DB_SERVER "127.0.0.1"
#define DB_UNAME "zyh"
#define DB_PASSWD "uchat_8888"
#define DB_NAME "uchat"

/*定义描述符集大小*/
#ifndef FD_SETSIZE
#define FD_SETSIZE 256
#endif


/*是否禁言*/
enum Flag{
	YES, //被禁言
	NO //未被禁言
};

/*消息类型枚举*/
enum MessageType{
	REGIST, //注册
	LOGIN, //登录
	LOGOUT,//登出
	LISTUSERS, //查看在线用户列表
	HISTRECORDS, //查看聊天记录
	GROUPCHAT, //群聊消息
	PRIVCHAT, //私聊消息
	EXIT, //下线
	RESULT, //结果消息
	UNKNOWN //未知类型
};

/*消息结果状态枚举*/
enum State{
	CONN_LIMIT, //连接已达上线
	SUCCESS, //成功
	FAIL, //失败
	UNREGIST,//未注册
	DUPLICATE_NAME, //用户名重复
	WRONGPWD, //密码错误
	NO_ONE_ONLINE, //无人在线
	NOT_ONLINE, //不在线
	ALREADY_ONLINE //已经在线
};

/*消息结构体*/
typedef struct _message{
	char recvName[MAX_NAME_LEN]; //接收用户名
	char sendName[MAX_NAME_LEN]; //发送用户名
	int msgType; //消息类型
	int state; //消息状态
	char content[MAX_MSGSIZE]; //消息内容
	struct sockaddr_in recvAddr; //接收端地址
	struct sockaddr_in sendAddr; //发送端地址
	char sendTime[MAX_NAME_LEN]; //发送时间
}Message;

/*客户端连接消息体*/
typedef struct s_data{
	int fd;
}sData;

/*用户信息结构体*/
typedef struct _user{
	int id;//用户id
	char name[MAX_NAME_LEN]; //用户名
	char passwd[MAX_NAME_LEN]; //密码
	int fd; //套接字描述符
	int state; //状态
	char regTime[20]; //注册时间
}User;

/*服务端接口定义*/
/*消息分发处理*/
void requestHandler(void *data);

/*登录逻辑处理*/
void login_s(Message *msg,int fd);
/*群聊*/
void groupChat(Message *msg,int fd);
/*私聊*/
void privChat(Message *msg,int fd);
/*注册*/
void registion_s(Message *msg,int fd);
/*查看在线用户列表*/
void listUsers(Message *msg,int fd);
/*查看历史消息记录*/
void histRecords(Message *msg,int fd);
/*登出*/
void logout_s(Message *msg,int fd);
/*获取错误消息*/
char *geterrmsg(int state);
/*用户自定义比较*/
int userCompare(void *u1,void *u2);
/*移除在线用户*/
void rmClient(int fd,int flags);
/*更新当前最大客户端连接描述符*/
void updateMaxFD(int fd);

/*客户端接口定义*/
/*登录*/
void login(int fd);

/*进入聊天室*/
void enterChat(User *user,int fd);

/*注册*/
void registion(int fd);

/*处理接收消息*/
void recvMsg(int *fd);

/*主界面提示*/
void mainInterface();

/*帮助信息*/
void helpInterface();

/*聊天类型展示接口*/
void chatTypeInterface();

/*显示在线用户列表*/
void listUsers_c(Message *msg);

/*数据库操作接口*/
/*获取连接*/
MYSQL *getCon();

/*新增用户*/
int addUser(User user);

/*修改状态*/
int updateUserState(const char *name,const int state);

/*根据名字获取用户信息*/
User *getUserByName(const char *name);

/*格式化错误信息*/
void errorMsg(MYSQL *con);


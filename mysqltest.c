#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<mysql.h>
#include<my_global.h>
#include<time.h>
#include<string.h>

typedef struct user{
	char name[20];
	char passwd[20];
	int state;
	char regTime[20];
}User;

int main(void){
	User user;
	MYSQL con;
	char buf[2];
	time_t timeout;
	time(&timeout);
	struct tm *now;
	now=localtime(&timeout);
	mysql_init(&con);
	if(mysql_real_connect(&con,"127.0.0.1","root","root","test",0,NULL,0)==NULL){
		printf("connect mysql error %d:%s\n",mysql_errno(&con),mysql_error(&con));
		_exit(1);
	}
	strcpy(user.name,"zyh");
	strcpy(user.passwd,"12345678");
	user.state=1;
	sprintf(user.regTime,"%d-%d-%d %d:%d:%d",now->tm_year+1900,now->tm_mon+1,now->tm_mday,now->tm_hour,now->tm_min,now->tm_sec);
	char sql[100]="insert into t_user values(NULL,'";
	strcat(sql,user.name);
	strcat(sql,"','");
	strcat(sql,user.passwd);
	strcat(sql,"','");
	sprintf(buf,"%d",user.state);
	buf[2]=0;
	strcat(sql,buf);
	strcat(sql,"',str_to_date('");
	strcat(sql,user.regTime);
	strcat(sql,"',");
	strcat(sql,"'%Y-%m-%d %H:%i:%s'))");
	printf("sql:%s\n",sql);
	my_bool result=mysql_query(&con,sql);
	printf("insert result:%d\n",result);
	if(result){
		printf("insert user error %d:%s\n",mysql_errno(&con),mysql_error(&con));
		mysql_close(&con);
		_exit(1);	
	}
	int id=mysql_insert_id(&con);
	mysql_close(&con);
	printf("success rows:%d\n",id);
	_exit(0);
}

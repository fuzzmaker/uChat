#include "../base/config.h"

MYSQL *getCon(){
	MYSQL *con;
	con=mysql_init(NULL);
	if(mysql_real_connect(con,DB_SERVER,DB_UNAME,DB_PASSWD,DB_NAME,0,NULL,0)==NULL){
		errorMsg(con);
		return NULL;
	}
	return con;
}


int addUser(User user){
	MYSQL *con=getCon();
	char buf[2];
	time_t timeout;
	time(&timeout);
	struct tm *now;
	now=localtime(&timeout);
	sprintf(user.regTime,"%d-%d-%d %d:%d:%d",now->tm_year+1900,now->tm_mon+1,now->tm_mday,now->tm_hour,now->tm_min,now->tm_sec);
	char sql[100]="insert into user values(NULL,'";
	strcat(sql,user.name);
	strcat(sql,"','");
	strcat(sql,user.passwd);
	strcat(sql,"','");
	sprintf(buf,"%d",user.state);
	strcat(sql,buf);
	strcat(sql,"',str_to_date('");
	strcat(sql,user.regTime);
	strcat(sql,"',");
	strcat(sql,"'%Y-%m-%d %H:%i:%s'))");
	printf("sql: %s\n",sql);
	if(mysql_query(con,sql)){
		printf("insert user error %d:%s\n",mysql_errno(con),mysql_error(con));
		mysql_close(con);
		return -1;
	}
	int id=mysql_insert_id(con);
	mysql_close(con);
	return id;                                                                                                                 
}


int updateUserState(const char *name,const int state){
	MYSQL *con=getCon();
	char sql[100]="update user set state='";
	char buf[2]={0};
	sprintf(buf,"%d",state);
	strcat(sql,buf);
	strcat(sql,"' where name='");
	strcat(sql,name);
	strcat(sql,"'");
	if(mysql_query(con,sql)){
		errorMsg(con);
		mysql_close(con);
		return 0;
	}
	mysql_close(con);
	return 1;
}

User *getUserByName(const char *name){
	User *user=NULL;
	MYSQL *con=getCon();
	char sql[100]="select * from user where name='";
	strcat(sql,name);
	strcat(sql,"'");
	printf("sql: %s\n",sql);
	if(mysql_query(con,sql)){
		errorMsg(con);	
		mysql_close(con);
		return NULL;
	}else{
		MYSQL_RES *result=mysql_store_result(con);
		if(result==NULL){
			errorMsg(con);
			mysql_close(con);
			return NULL;

		}
		int rownum=mysql_num_rows(result);
		if(rownum<=0){
			mysql_close(con);
			return NULL;
		}
		user=malloc(sizeof(struct _user));
		MYSQL_ROW row=mysql_fetch_row(result);
		user->id=atoi(row[0]);
		strcpy(user->name,row[1]?row[1]:"");
		strcpy(user->passwd,row[2]?row[2]:"");
		user->state=atoi(row[3]?row[3]:"-1");
		strcpy(user->regTime,row[4]?row[4]:"");
		mysql_free_result(result);
		mysql_close(con);
		return user;
	}
}

void errorMsg(MYSQL *con){
	printf("error %d:%s\n",mysql_errno(con),mysql_error(con));
}

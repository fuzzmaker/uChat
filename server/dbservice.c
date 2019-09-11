#include "../base/config.h"

MYSQL *getCon(){
	MYSQL con;
	mysql_init(&con);
	if(mysql_real_connect(&con,DB_SERVER,DB_UNAME,DB_PASSWD,DB_NAME,0,NULL,0)==NULL){
		errorMsg(&con);
		return NULL;
	}
	return &con;
}


int addUser(User user){
	MYSQL *con=getCon();
	char buf[2];
	time_t timeout;
	time(&timeout);
	struct tm *now;
	now=localtime(&timeout);
	mysql_init(con);
	if(mysql_real_connect(con,"127.0.0.1","root","root","test",0,NULL,0)==NULL){
		printf("connect mysql error %d:%s\n",mysql_errno(con),mysql_error(con));
		_exit(1);
	}
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
	char sql[100]="update t_user set state='";
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
	User user;
	MYSQL *con=getCon();
	char sql[100]="select * from t_user where name='";
	strcat(sql,name);
	strcat(sql,"'");
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
		int num=mysql_num_fields(result);
		MYSQL_ROW row=mysql_fetch_row(result);
		user.id=row[0];
		user.name=row[1]?row[1]:"";
		user.passwd=row[2]?row[2]:"";
		user.state=row[3]?row[3]:-1;
		user.regTime=row[4]?row[4]:"";
		mysql_free_result(result);
		mysql_close(con);
		return &user;
	}
}

void errorMsg(MYSQL *con){
	fprintf(stderr,"error %d:%s\n",mysql_errno(con),mysql_error(con));
}

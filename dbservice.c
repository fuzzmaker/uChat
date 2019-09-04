#include "config.h"

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
	time_t time;
	time(&time);
	struct tm *now=localtime(&time);
	sprintf(user.regTime,"%d-%d-%d %d:%d:%d",tm->tm_year+1900,tm->tm_mon+1,tm->tm_hour,tm->tm_min,tm->tm_sec);
	char *sql="insert into t_user values(";
	strcat(sql,user.name);
	strcat(sql,",");
	strcat(sql,user.passwd);
        strcat(sql,",");
	strcat(sql,user.state);
        strcat(sql,",str_to_date('");
	strcat(sql,user.regTime);
        strcat(sql,",'%Y-%m-%d %H:%m:%i'))");
	if(!mysql_query(con,sql)){
		errorMsg(con);
		mysql_close(con);
		return 0;
	}
	mysql_close(con);
	return 1;
}


void updateUser(User user){
	MYSQL *con=getCon();
	mysql_close(con);
}

User *getUserByName(char *name){
	User user;
	MYSQL *con=getCon();
	char *sql="select * from t_user where name=";
	strcat(sql,name)
	if(!mysql_query(con,sql)){
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

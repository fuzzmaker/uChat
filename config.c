#include "config.h"

char *geterrmsg(int state){
	switch(state){
		case SUCCESS:
			return "成功";
		case FAIL:
			return "失败";
		case UNREGISTION:
			return "账户未注册";
		case WRONGPASSWD:
			return "密码错误";
		case DUPLICATE_NAME:
			return "用户名重复";
		case NO_ONE_ONLINE:
			return "无人在线";
		case ALREADY_ONLINE:
			return "已上线";
		case CONN_LIMIT:
			return "连接已达上线";
		case NOT_ONLINE:
			return "对方不在线";
		default :
			return "未知状态";
	}
}

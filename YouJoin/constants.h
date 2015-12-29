//存放程序用到的常量

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>

namespace YJ_CONSTANTS{
	//登录界面的请求类型
	//用户登录 0
	//用户注册 1
	const int POST_SIGNIN = 0;
	const int POST_SIGNUP = 1;

	//用户注册登录端口
	const int PORT_SIGN = 5155;
	//用户在线状态验证端口
	const int PORT_LOG_STATE = 5156;

	//服务器udp数据获取端口
	const int PORT_GET_DATA_SERVER = 5157;
	//客户端udp数据获取端口
	const int PORT_GET_DATA_CLIENT = 5163;

	//客户端接收消息推送端口
	const int PORT_GET_MSG = 5162;

	//用户聊天发送信息端口
	const int PORT_CHAT_SEND = 5160;
	//用户聊天接受信息端口
	const int PORT_CHAT_RECEIVE = 5161;


	//数据传送标识
	const int GET_DATA_NONE = 0;
	//通过userid获取userinfo
	const int GET_DATA_USERINFO = 1;
	//更新userinfo
	const int UPDATE_DATA_USERINFO = 2;
	//通过userid获取好友推荐列表
	const int GET_DATA_RECOMMAND = 3;
	//添加userid为好友
	const int ADD_FRIEND = 4;
	//发送动态
	const int POST_PUBLIC_MSG = 5;
	//发送私信
	const int SEND_PRIVATE_MSG = 6;


	//服务器IP地址
	const QString IPADDRESS_LOCALHOST = "127.0.0.1";
	const QString IPADDRESS_REMOTEHOST = "125.216.250.79";

	//在线验证信息
	const QString ONLINE_CHECK_MSG = "online";

	//客户端发送验证信息的时间间隔/毫秒 60000
	const int PUSH_INTERVAL = 10000;
	//客户端发送验证信息的等待时间/毫秒
	const int PUSH_WAIT_INTERVAL = 5000;
	//服务器检测用户在线的时间间隔/毫秒 180000
	const int CHECK_INTERVAL = 30000;


	//服务端用户在线table水平表头数量
	const int TABLE_HEADER_COUNT = 3;
	//服务端用户在线table水平表头项目枚举
	const int USER_ID = 0;
	const int USER_NAME = 1;
	const int USER_IP = 2;

	const QString TABLE_HEADERS_STRING[TABLE_HEADER_COUNT] = {
		QString::fromLocal8Bit("用户ID"),
		QString::fromLocal8Bit("用户名"),
		QString::fromLocal8Bit("IP地址")
	};

	//服务器数据文件名
	const char DATA_FILE_NAME[] = "users_information.youjoin";
	//服务器索引文件名
	const char INDEX_FILE_NAME[] = "key_and_value.youjoin";
	//服务器全用户id文件名
	const char USERID_FILE_NAME[] = "alluserid.youjoin";

	enum HOBBIES{
		SPORT, TOUR, CARTON, PHOTO, MOVIE, SCIENCE, DIGIT
	};


}



#endif //CONSTANTS_H
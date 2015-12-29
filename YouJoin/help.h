//全局辅助类
//类名：YJ_Help
//功能：
//提供网络连接服务
//界面管理
//全局信息存储

#ifndef HELP_H
#define HELP_H

#include <QObject>
#include <QtWidgets>
#include "userinfo.h"
#include "formlogin.h"
#include "formmain.h"
#include <QtNetwork>
#include "logstatethread.h"

#include <vector>
using std::vector;


class YJ_Help : public QObject{


	Q_OBJECT

public:
	YJ_Help(QObject *parent = 0);
	~YJ_Help();


signals:
	
private slots :
	
	//登陆成功信号处理函数
	void yjh_login_success();

	//发送在线验证消息
	void yjh_push_log_state();

	//发送心情动态
	void yjh_push_public_msg(QString msg);
	
	//void yjh_receive_data();

	//更新用户详细信息
	void yjh_update_detail();

	//添加好友
	void yjh_add_friend(int userid);

	//处理udp socket获取的数据
	void yjh_udp_receive_data();

private:
	
	//显示登录界面
	void yjh_init_login();

	//初始化信号-槽连接
	void yjh_init_connections();

	//初始化timer
	void yjh_init_timer();

	//void yjh_connect_data_server();

	//更新数据
	void yjh_update_data();

	//数据获取接口
	void yjh_request_data(int getDataType, int userid = 0);

	//处理服务器返回的json数据包
	void yjh_parse_data_json(QByteArray &data);

	YJ_Login_Form *loginForm;
	YJ_Main_Form *mainForm = NULL;
	user_info userInfo;

	//数据接收/发送udp
	QUdpSocket *udpReceiver;
	QUdpSocket *udpSender;

	//登录状态发送
	QTcpSocket stateSocket;
	
	QTimer stateTimer;

	QString publictext;
	int addid;
	vector<user_info> friends;

	//QTcpSocket recommandSocket;
	//QTcpSocket dataSocket;
	//quint16 dataBlockSize = 0;
	//int getDataType;
	
	bool isLogin = false;

};

#endif //HELP_H
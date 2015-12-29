//登录窗体
//类名：YJ_Login_Form
//功能：提供用户登录功能
//		注册功能

#ifndef FORM_LOGIN_H
#define FORM_LOGIN_H

#include <QtWidgets/QWidget>
#include "ui_loginform.h"
#include <qwidgetresizehandler_p.h>
#include <QPainter>
#include <QIcon>

#include <QMessageBox>
#include <QString>
#include <QJsonDocument>
#include <QVariantMap>
#include <QVariantList>
#include <QtNetwork>
#include "constants.h"
#include "userinfo.h"
#include "ipushbutton.h"

#include <vector>
using std::vector;


class YJ_Login_Form : public QWidget
{
	Q_OBJECT

public:
	YJ_Login_Form(QWidget *parent = 0);
	~YJ_Login_Form();

	//获取当前用户的信息
	user_info YJ_get_curr_userinfo(){
		return info;
	}

	//获取当前用户的好友列表
	vector<user_info> YJ_get_friend_vec(){
		return friends;
	}

private slots:

	//登录、注册按钮单机槽
	void yj_signin_button_clicked();
	void yj_signup_button_clicked();

	//连接登录服务器
	void yj_connect_server();

	//连接成功，准备读取登录结果
	void yj_haved_connected();

	//网络连接错误处理
	void yj_display_error(QAbstractSocket::SocketError);

	//接收服务器发送的数据
	void yj_accept_msg();

	//向服务器发送数据
	void yj_send_msg(QJsonDocument &data);

signals:

	//登录成功信号
	void YJ_Login_Success();

private:

	//绘制窗体背景图
	void paintEvent(QPaintEvent *event);

	//初始化窗体UI
	void yj_init_ui();

	//初始化信号-槽连接
	void yj_init_connections();

	//初始化待发送的数据
	void yj_init_send_data(int data_type);

	//解析服务器发来的json数据包
	void yj_parse_json(QByteArray &data);


	user_info info;
	QVariantMap info_map;

	vector<user_info> friends;

	QTcpSocket *tcpClient;

	I_PushButton *exitButton;

	//QString localMessage; // 存放本地要发送的信息
	//QString serverMessage;  //存放从服务器接收到的信息
	quint16 blockSize;  //存放接收到的信息大小
	Ui::login_form ui;
	
};

#endif // FORM_LOGIN_H
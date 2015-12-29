//好友页面
//类名：YJ_Friend_Block
//功能：显示好友列表，与好友进行即时聊天

#ifndef FRIEND_BLOCK_H
#define FRIEND_BLOCK_H

#include "ui_friendblock.h"
#include <QtWidgets>
#include <QtNetwork>
#include "nofocusdelegate.h"
#include "constants.h"
#include "userinfo.h"
#include <vector>
using std::vector;

class YJ_Friend_Block : public QWidget{

	Q_OBJECT

public:

	YJ_Friend_Block(QWidget *parent = 0);
	~YJ_Friend_Block();

	//设置当前用户信息，好友列表
	void YJ_set_userinfo(user_info u, const vector<user_info> &friendlist);

private slots:
	
	//发送按钮单机槽
	void yj_send_button_clicked();
	
	//收到消息
	void yj_receive_msg();

	//双击好友列表的某个好友，开始聊天
	void yj_friend_table_item_dblclick(int row, int column);

private:

	//初始化ui
	void yj_init_ui();

	//初始化信号-槽连接
	void yj_init_connections();
	
	//初始化网络模块
	void yj_init_network();

	//捕捉键盘回车键
	bool eventFilter(QObject *obj, QEvent *e);
	
	//发送消息
	void yj_send_msg(QString &msg);

	//更新好友列表
	void yj_refresh_friend_table();

	//设置好友列表的背景颜色
	void yj_set_friend_table_backgroud();


	Ui::FriendBlock ui;

	QBrush *receive_brush;
	QBrush *send_brush;

	QUdpSocket *UdpSender;
	QUdpSocket *UdpReader;

	QString localmsg;
	QString receivemsg;

	int now_chat_userid;
	int now_row = -1;
	user_info info;
	vector<user_info> friends;
};

#endif //FRIEND_BLOCK_H
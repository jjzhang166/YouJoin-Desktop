//用户信息块
//类名：YJ_User_Block
//功能：在窗体中显示一个包含用户头像、用户名、在线状态的块
//		按下按钮可切换在线/隐身状态

#ifndef	USER_BLOCK_H
#define USER_BLOCK_H

#include "ui_userblock.h"

#include <QtWidgets/QWidget>
#include <QPainter>
#include <QIcon>

class YJ_User_Block : public QWidget{

	Q_OBJECT

public :

	YJ_User_Block(bool state, QString user, QWidget *parent = 0);

	~YJ_User_Block();

	//设置按钮状态
	void YJ_set_button_state(bool state);

	//设置用户名
	void YJ_set_username(QString user);

private slots:
	
	//按钮单击事件
	void yj_statecut_button_click();


private:

	//绘制部件背景
	void paintEvent(QPaintEvent *event);

	//初始化部件UI
	void yj_init_ui();

	//初始化部件信号-槽连接
	void yj_init_connection();

	//初始化用户登录信息
	void yj_init_info(bool state, QString user);

	Ui::UserBlock ui;
	
	bool button_state;

	QString username;


};

#endif //USER_BLOCK_H
//用户资料卡

#ifndef USERINFO_CARD_H
#define USERINFO_CARD_H

#include <QObject>
#include <QtWidgets>
#include "ui_userinfocard.h"
#include "userinfo.h"
#include <qwidgetresizehandler_p.h>

class YJ_User_Info_Card : public QWidget{

	Q_OBJECT
	
public:
	
	YJ_User_Info_Card(user_info info, QWidget *parent = 0,
		bool showAddButton = true);
	~YJ_User_Info_Card(){}

signals:

	//添加好友按钮信号
	void YJ_add_friend(int userid);

private slots:
	//添加好友按钮单击
	void yj_add_button_clicked();

private:
	
	void yj_init_ui();
	void yj_init_connections();
	//绘制窗体背景图
	void paintEvent(QPaintEvent *event);

	user_info user;
	Ui::userinfocard ui;
	bool isShowAddButton;
};

#endif //USERINFO_CARD_H
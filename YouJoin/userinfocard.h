//�û����Ͽ�

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

	//��Ӻ��Ѱ�ť�ź�
	void YJ_add_friend(int userid);

private slots:
	//��Ӻ��Ѱ�ť����
	void yj_add_button_clicked();

private:
	
	void yj_init_ui();
	void yj_init_connections();
	//���ƴ��屳��ͼ
	void paintEvent(QPaintEvent *event);

	user_info user;
	Ui::userinfocard ui;
	bool isShowAddButton;
};

#endif //USERINFO_CARD_H
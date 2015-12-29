//�û���Ϣ��
//������YJ_User_Block
//���ܣ��ڴ�������ʾһ�������û�ͷ���û���������״̬�Ŀ�
//		���°�ť���л�����/����״̬

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

	//���ð�ť״̬
	void YJ_set_button_state(bool state);

	//�����û���
	void YJ_set_username(QString user);

private slots:
	
	//��ť�����¼�
	void yj_statecut_button_click();


private:

	//���Ʋ�������
	void paintEvent(QPaintEvent *event);

	//��ʼ������UI
	void yj_init_ui();

	//��ʼ�������ź�-������
	void yj_init_connection();

	//��ʼ���û���¼��Ϣ
	void yj_init_info(bool state, QString user);

	Ui::UserBlock ui;
	
	bool button_state;

	QString username;


};

#endif //USER_BLOCK_H
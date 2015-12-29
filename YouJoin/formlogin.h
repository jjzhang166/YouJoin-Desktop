//��¼����
//������YJ_Login_Form
//���ܣ��ṩ�û���¼����
//		ע�Ṧ��

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

	//��ȡ��ǰ�û�����Ϣ
	user_info YJ_get_curr_userinfo(){
		return info;
	}

	//��ȡ��ǰ�û��ĺ����б�
	vector<user_info> YJ_get_friend_vec(){
		return friends;
	}

private slots:

	//��¼��ע�ᰴť������
	void yj_signin_button_clicked();
	void yj_signup_button_clicked();

	//���ӵ�¼������
	void yj_connect_server();

	//���ӳɹ���׼����ȡ��¼���
	void yj_haved_connected();

	//�������Ӵ�����
	void yj_display_error(QAbstractSocket::SocketError);

	//���շ��������͵�����
	void yj_accept_msg();

	//���������������
	void yj_send_msg(QJsonDocument &data);

signals:

	//��¼�ɹ��ź�
	void YJ_Login_Success();

private:

	//���ƴ��屳��ͼ
	void paintEvent(QPaintEvent *event);

	//��ʼ������UI
	void yj_init_ui();

	//��ʼ���ź�-������
	void yj_init_connections();

	//��ʼ�������͵�����
	void yj_init_send_data(int data_type);

	//����������������json���ݰ�
	void yj_parse_json(QByteArray &data);


	user_info info;
	QVariantMap info_map;

	vector<user_info> friends;

	QTcpSocket *tcpClient;

	I_PushButton *exitButton;

	//QString localMessage; // ��ű���Ҫ���͵���Ϣ
	//QString serverMessage;  //��Ŵӷ��������յ�����Ϣ
	quint16 blockSize;  //��Ž��յ�����Ϣ��С
	Ui::login_form ui;
	
};

#endif // FORM_LOGIN_H
//ȫ�ָ�����
//������YJ_Help
//���ܣ�
//�ṩ�������ӷ���
//�������
//ȫ����Ϣ�洢

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
	
	//��½�ɹ��źŴ�����
	void yjh_login_success();

	//����������֤��Ϣ
	void yjh_push_log_state();

	//�������鶯̬
	void yjh_push_public_msg(QString msg);
	
	//void yjh_receive_data();

	//�����û���ϸ��Ϣ
	void yjh_update_detail();

	//��Ӻ���
	void yjh_add_friend(int userid);

	//����udp socket��ȡ������
	void yjh_udp_receive_data();

private:
	
	//��ʾ��¼����
	void yjh_init_login();

	//��ʼ���ź�-������
	void yjh_init_connections();

	//��ʼ��timer
	void yjh_init_timer();

	//void yjh_connect_data_server();

	//��������
	void yjh_update_data();

	//���ݻ�ȡ�ӿ�
	void yjh_request_data(int getDataType, int userid = 0);

	//������������ص�json���ݰ�
	void yjh_parse_data_json(QByteArray &data);

	YJ_Login_Form *loginForm;
	YJ_Main_Form *mainForm = NULL;
	user_info userInfo;

	//���ݽ���/����udp
	QUdpSocket *udpReceiver;
	QUdpSocket *udpSender;

	//��¼״̬����
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
//����ҳ��
//������YJ_Friend_Block
//���ܣ���ʾ�����б�����ѽ��м�ʱ����

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

	//���õ�ǰ�û���Ϣ�������б�
	void YJ_set_userinfo(user_info u, const vector<user_info> &friendlist);

private slots:
	
	//���Ͱ�ť������
	void yj_send_button_clicked();
	
	//�յ���Ϣ
	void yj_receive_msg();

	//˫�������б��ĳ�����ѣ���ʼ����
	void yj_friend_table_item_dblclick(int row, int column);

private:

	//��ʼ��ui
	void yj_init_ui();

	//��ʼ���ź�-������
	void yj_init_connections();
	
	//��ʼ������ģ��
	void yj_init_network();

	//��׽���̻س���
	bool eventFilter(QObject *obj, QEvent *e);
	
	//������Ϣ
	void yj_send_msg(QString &msg);

	//���º����б�
	void yj_refresh_friend_table();

	//���ú����б�ı�����ɫ
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
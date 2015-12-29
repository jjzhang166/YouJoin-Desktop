//������
//������YJ_Main_Form
//���ܣ�����һ���Զ��������͸�����ģ��

#ifndef FORM_HOMEPAGE_H
#define FORM_HOMEPAGE_H

#include "ui_mainform.h"
#include "sidebar.h"
#include "userblock.h"
#include "musicblock.h"
#include "friendblock.h"
#include "userinfo.h"
#include "weatherblock.h"
#include "forminfocollect.h"
#include "moreblock.h"
#include "recommandblock.h"
#include "photoblock.h"
#include "userinfocard.h"
#include "nofocusdelegate.h"

#include <QtWidgets/QWidget>
#include <qwidgetresizehandler_p.h>
#include <QPainter>
#include <QIcon>
#include <vector>
using std::vector;

class YJ_Main_Form : public QWidget{
	
	Q_OBJECT

public :
	
	YJ_Main_Form(QWidget *parent = 0);
	
	~YJ_Main_Form();

	//���ô��屳��ͼƬ
	void YJ_set_background(QString &pic);

	//�����û�
	void YJ_set_user(user_info user, const vector<user_info> &friendlist);

	//��ȡ��ǰ�û���Ϣ
	user_info YJ_get_user_info();

	//��ȡ��ǰ�û���ϸ����
	user_detail YJ_get_user_detail();

	//���ú����Ƽ��б�
	void YJ_set_recommand_list(QList<user_info> list);

	//�յ����ѷ��͵����鶯̬
	void YJ_receive_msg(QVariantMap dataMap);

signals:

	//�û���ϸ���ϸ����ź�
	void YJ_Detail_Update();

	//��Ӻ����ź�
	void YJ_add_friend(int userid);

	//�û��������鶯̬�ź�
	void YJ_push_public_msg(QString msg);

private slots:
	
	//�л�ģ��ҳ
	void yj_cut_page(int button_flag);

	//�����û���ϸ��Ϣ
	void yj_update_detail();

	//ͬ�������б�
	void yj_refresh_musiclist();

	//��ʾ�Լ������Ͽ�
	void yj_show_self();

	//�˳�����
	void yj_quit();

	//���Ͷ�̬
	void yj_send_button_clicked();

private:

	//���ƴ��屳��ͼ
	void paintEvent(QPaintEvent *event);

	//��ʼ��UI����
	void yj_init_ui();

	//��ʼ����ģ���Ԫ��Ϣ
	void yj_init_metadata();

	//��ʼ���ź�-������
	void yj_init_connections();

	//��������ģ��ҳ
	void yj_delete_all_pages();

	//��������ģ��ҳ
	void yj_invisiable_all_pages();

	//������ҳ����
	void yj_invisiable_main_page();

	//��ʾ��ҳ����
	void yj_visiable_main_page();

	//�л�����ͬ��ģ��ҳ
	void yj_page_to_homepage();
	void yj_page_to_friend();
	void yj_page_to_recommend();
	void yj_page_to_photo();
	void yj_page_to_music();
	void yj_page_to_video();
	void yj_page_to_more();

	//������ϸ����
	void yj_set_detail(user_detail detail);

	//������Ϣtable
	void yj_add_msg_table();

	Ui::main_form ui;

	YJ_Sidebar *sidebar = NULL;
	YJ_User_Block *userblock = NULL;
	YJ_Music_Block *musicblock = NULL;
	YJ_Friend_Block *friendblock = NULL;
	YJ_Weather_Block *weatherblock = NULL;
	YJ_InfoCollection_Form *infocollectionform = NULL;
	YJ_More_Block *moreblock = NULL;
	YJ_Recommand_Block *recommandBlock = NULL;
	YJ_Photo_Block *photoblock = NULL;

	YJ_User_Info_Card *infoCard = NULL;

	user_info info;
	vector<user_info> friends;

	QString background_pic;
	QString background_group[7];

	QBrush *msgtable_item = NULL;

	QStringList msgList;
};

#endif //FORM_HOMEPAGE_H
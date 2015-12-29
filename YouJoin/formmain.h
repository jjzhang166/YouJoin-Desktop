//主窗体
//类名：YJ_Main_Form
//功能：承载一个自定义侧边栏和各种子模块

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

	//设置窗体背景图片
	void YJ_set_background(QString &pic);

	//设置用户
	void YJ_set_user(user_info user, const vector<user_info> &friendlist);

	//获取当前用户信息
	user_info YJ_get_user_info();

	//获取当前用户详细资料
	user_detail YJ_get_user_detail();

	//设置好友推荐列表
	void YJ_set_recommand_list(QList<user_info> list);

	//收到好友发送的心情动态
	void YJ_receive_msg(QVariantMap dataMap);

signals:

	//用户详细资料更新信号
	void YJ_Detail_Update();

	//添加好友信号
	void YJ_add_friend(int userid);

	//用户发送心情动态信号
	void YJ_push_public_msg(QString msg);

private slots:
	
	//切换模块页
	void yj_cut_page(int button_flag);

	//更新用户详细信息
	void yj_update_detail();

	//同步播放列表
	void yj_refresh_musiclist();

	//显示自己的资料卡
	void yj_show_self();

	//退出程序
	void yj_quit();

	//发送动态
	void yj_send_button_clicked();

private:

	//绘制窗体背景图
	void paintEvent(QPaintEvent *event);

	//初始化UI界面
	void yj_init_ui();

	//初始化各模块的元信息
	void yj_init_metadata();

	//初始化信号-槽连接
	void yj_init_connections();

	//销毁所有模块页
	void yj_delete_all_pages();

	//隐藏所有模块页
	void yj_invisiable_all_pages();

	//隐藏主页内容
	void yj_invisiable_main_page();

	//显示主页内容
	void yj_visiable_main_page();

	//切换到不同的模块页
	void yj_page_to_homepage();
	void yj_page_to_friend();
	void yj_page_to_recommend();
	void yj_page_to_photo();
	void yj_page_to_music();
	void yj_page_to_video();
	void yj_page_to_more();

	//设置详细资料
	void yj_set_detail(user_detail detail);

	//更新消息table
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
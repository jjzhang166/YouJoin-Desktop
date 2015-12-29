//自定义侧边栏部件
//类名：YJ_Sidebar
//功能：在窗体中显示一个侧边栏，包含一系列按钮
//		按下不同按钮时会有切换效果

#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QtWidgets/QWidget>
#include "ui_sidebar.h"
#include <QPainter>
#include <QIcon>
#include <QString>
#include "ipushbutton.h"

//将每个按钮的信息封装起来
struct Button_Info{
	//按钮指针
	//QPushButton *name;
	I_PushButton *name;

	//按钮的状态，true表示按下，false表示未按下
	bool state;
	
	//按钮按下时的图标
	QString pushed_icon;
	
	//按钮未按下时的图标
	QString unpushed_icon;
};

//给按钮编号
enum BUTTON_FLAG{
	HOMEPAGE, FRIEND, RECOMMEND, PHOTO, MUSIC, VIDEO, MORE
};

class YJ_Sidebar : public QWidget
{
	Q_OBJECT

public :
	YJ_Sidebar(QWidget *parent = 0);
	~YJ_Sidebar();

signals:
	//一系列按钮的单击信号
	void yj_homepage_button_clicked(int);
	void yj_friend_button_clicked(int);
	void yj_recommend_button_clicked(int);
	void yj_photo_button_clicked(int);
	void yj_music_button_clicked(int);
	void yj_video_button_clicked(int);
	void yj_more_button_clicked(int);


private slots:
	//一系列按钮的单击事件
	void yj_homepage_button_click();
	void yj_friend_button_click();
	void yj_recommend_button_click();
	void yj_photo_button_click();
	void yj_music_button_click();
	void yj_video_button_click();
	void yj_more_button_click();

private:
	//绘制部件背景
	void paintEvent(QPaintEvent *event);

	//初始化部件UI
	void yj_init_ui();

	//初始化部件信号-槽连接
	void yj_init_connections();

	//初始化各按钮信息、状态、图标
	void yj_init_button_info();

	//获取当前按下的按钮编号
	int yj_get_pushed_button();

	//设置按钮为按下状态
	void yj_set_pushed_button(int button_flag);

	//设置按钮为未按下状态
	void yj_set_unpushed_button(int button_flag);

	
	Ui::Sidebar ui;

	//按钮组
	Button_Info button_group[7];


};



#endif //SIDEBAR_H
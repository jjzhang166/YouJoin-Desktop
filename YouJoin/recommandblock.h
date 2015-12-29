//推荐页面

#ifndef RECOMMAND_BLOCK_H
#define RECOMMAND_BLOCK_H

#include <QObject>
#include <QtWidgets>
#include <QList>

#include "ui_recommandblock.h"
#include "nofocusdelegate.h"
#include "userinfo.h"
#include "constants.h"
#include "searchbar.h"
#include "userinfocard.h"

class YJ_Recommand_Block : public QWidget{
	
	Q_OBJECT

public:
	YJ_Recommand_Block(QWidget *parent = 0);
	~YJ_Recommand_Block(){}

	//设置音乐列表
	void YJ_set_musiclist(QStringList);

	//设置好友推荐列表
	void YJ_set_friendlist(QList<user_info>);

signals:

	//添加好友信号
	void YJ_add_friend(int userid);

private slots:

	//好友列表项目双击事件
	void yj_friend_table_item_dblclick(int row, int column);

	//添加好友
	void yj_add_friend(int userid);

private:

	//初始化ui
	void yj_init_ui();

	//初始化信号-槽
	void yj_init_connections();

	//更新音乐table
	void yj_update_music_table();

	//更新好友table
	void yj_update_friend_table();

	//设置table背景颜色
	void yj_set_music_table_background();
	void yj_set_friend_table_backgroud();

	QList<user_info> friendlist;

	YJ_Search_Bar *searchBar;
	QStringList musicList;
	QStringList friendList;

	YJ_User_Info_Card *infoCard = NULL;

	Ui::RecommandBlock ui;
};

#endif //RECOMMAND_BLOCK_H
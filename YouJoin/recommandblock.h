//�Ƽ�ҳ��

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

	//���������б�
	void YJ_set_musiclist(QStringList);

	//���ú����Ƽ��б�
	void YJ_set_friendlist(QList<user_info>);

signals:

	//��Ӻ����ź�
	void YJ_add_friend(int userid);

private slots:

	//�����б���Ŀ˫���¼�
	void yj_friend_table_item_dblclick(int row, int column);

	//��Ӻ���
	void yj_add_friend(int userid);

private:

	//��ʼ��ui
	void yj_init_ui();

	//��ʼ���ź�-��
	void yj_init_connections();

	//��������table
	void yj_update_music_table();

	//���º���table
	void yj_update_friend_table();

	//����table������ɫ
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
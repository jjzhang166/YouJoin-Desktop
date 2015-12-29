//搜索条

#ifndef SEARCH_BAR_H
#define SEARCH_BAR_H

#include <QObject>
#include <QWidget>
#include "ui_searchbar.h"
#include "trieTree.h"
#include <QTextCodec>
#include <vector>
#include "nofocusdelegate.h"
using std::vector;

class YJ_Search_Bar : public QWidget {

	Q_OBJECT

public:

	YJ_Search_Bar(QWidget *parent = 0);
	~YJ_Search_Bar(){};

	//设置音乐列表
	void YJ_set_music_list(QStringList list);

	//设置好友列表
	void YJ_set_friend_list(QStringList list);

signals:
	

private slots:

	//在trie树中搜索字符串
	void yj_search_trie(const QString & str);

private:
	
	void yj_init_ui();
	void yj_init_connections();

	//初始化trie树
	void yj_init_music_trie();
	void yj_init_friend_trie();
	void yj_init_trie();

	//将qstring转化为gb2312格式的char*数组
	char *yj_qstring_to_gb2312(QString &str);

	//更新table显示
	void yj_update_music_table();
	void yj_update_friend_table();

	//bool eventFilter(QObject *obj, QEvent *e);

	chTrieTree *musicTrie = NULL;
	chTrieTree *friendTrie = NULL;

	QStringList musicContentList;
	QStringList musicResultList;

	QStringList friendContentList;
	QStringList friendResultList;

	Ui::search_bar ui;

};

#endif //SEARCH_BAR_H
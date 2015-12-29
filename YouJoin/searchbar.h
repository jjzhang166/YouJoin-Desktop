//������

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

	//���������б�
	void YJ_set_music_list(QStringList list);

	//���ú����б�
	void YJ_set_friend_list(QStringList list);

signals:
	

private slots:

	//��trie���������ַ���
	void yj_search_trie(const QString & str);

private:
	
	void yj_init_ui();
	void yj_init_connections();

	//��ʼ��trie��
	void yj_init_music_trie();
	void yj_init_friend_trie();
	void yj_init_trie();

	//��qstringת��Ϊgb2312��ʽ��char*����
	char *yj_qstring_to_gb2312(QString &str);

	//����table��ʾ
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
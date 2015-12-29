#include "searchbar.h"

YJ_Search_Bar::YJ_Search_Bar(QWidget *parent /* = 0 */)
: QWidget(parent)
{
	ui.setupUi(this);
	//ui.search_edit->installEventFilter(this);
	yj_init_ui();
	yj_init_trie();
	yj_init_connections();
}

void YJ_Search_Bar::yj_init_ui()
{
	//去除标题栏
	this->setWindowFlags(Qt::FramelessWindowHint);
	//固定大小
	this->setFixedSize(424, 425);
	//背景透明
	setAttribute(Qt::WA_TranslucentBackground);

	QIcon icon_list_button;
	icon_list_button.addFile(":/YouJoin/Resources/list-button.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.list_button->setIcon(icon_list_button);
	ui.list_button->setFlat(true);
	ui.list_button->setFocusPolicy(Qt::NoFocus);
	//ui.list_button->setIconSize(QSize(22, 20));

	if (ui.result_table->columnCount() < 1)
		ui.result_table->setColumnCount(1);
	QTableWidgetItem *HeaderItem = new QTableWidgetItem();
	HeaderItem->setText("result");
	ui.result_table->setHorizontalHeaderItem(0, HeaderItem);

	//设置列宽
	ui.result_table->setColumnWidth(0, 424);

	//禁止编辑单元格内容
	ui.result_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//禁止选中
	ui.person_result_table->setSelectionMode(QAbstractItemView::NoSelection);
	//去掉水平滚动条
	ui.result_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//垂直滚动条按项移动
	ui.result_table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	//去除水平表头
	ui.result_table->horizontalHeader()->setFixedHeight(0);
	//去除垂直表头
	ui.result_table->verticalHeader()->setFixedWidth(0);
	//设置无边框
	ui.result_table->setFrameShape(QFrame::NoFrame);
	//设置不显示格子线
	ui.result_table->setShowGrid(false);
	//设置右键菜单
	ui.result_table->setContextMenuPolicy(Qt::CustomContextMenu);

	//设置背景颜色
	QPalette pal;
	pal.setBrush(QPalette::Base, QBrush(QColor(255, 255, 255, 98)));
	ui.result_table->setPalette(pal);

	//设置竖直滚动条样式
	ui.result_table->setStyleSheet(
		"QScrollBar{ width: 5px;background-color: rgb(255, 255, 255);}"
		"QScrollBar::handle{background:rgb(61, 11, 5); border:2px solid transparent; border-radius:3px;}"
		"QScrollBar::handle:hover{background:rgb(42, 9, 9);border:3px solid transparent; border-radius:3px;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}"
		"QTableWidget::item:selected { background-color: rgb(97, 17, 7) }");
	//半透明
	//ui.result_table->setAttribute(Qt::WA_TranslucentBackground);
	ui.result_table->verticalHeader()->setDefaultSectionSize(50);
	ui.result_table->setTextElideMode(Qt::ElideNone);

	ui.result_table->setItemDelegate(new NoFocusDelegate());
	ui.result_table->setVisible(false);

	ui.pic_label->setPixmap(QPixmap(":/YouJoin/Resources/searchmusic.png"));
	ui.pic_label->setVisible(false);


	if (ui.person_result_table->columnCount() < 1)
		ui.person_result_table->setColumnCount(1);
	QTableWidgetItem *HeaderItem2 = new QTableWidgetItem();
	HeaderItem2->setText("result");
	ui.person_result_table->setHorizontalHeaderItem(0, HeaderItem2);

	//设置列宽
	ui.person_result_table->setColumnWidth(0, 424);

	//禁止编辑单元格内容
	ui.person_result_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//禁止选中
	ui.person_result_table->setSelectionMode(QAbstractItemView::NoSelection);
	//去掉水平滚动条
	ui.person_result_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//垂直滚动条按项移动
	ui.person_result_table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	//去除水平表头
	ui.person_result_table->horizontalHeader()->setFixedHeight(0);
	//去除垂直表头
	ui.person_result_table->verticalHeader()->setFixedWidth(0);
	//设置无边框
	ui.person_result_table->setFrameShape(QFrame::NoFrame);
	//设置不显示格子线
	ui.person_result_table->setShowGrid(false);
	//设置右键菜单
	ui.person_result_table->setContextMenuPolicy(Qt::CustomContextMenu);

	//设置背景颜色
	ui.person_result_table->setPalette(pal);

	//设置竖直滚动条样式
	ui.person_result_table->setStyleSheet(
		"QScrollBar{ width: 5px;background-color: rgb(255, 255, 255);}"
		"QScrollBar::handle{background:rgb(35, 55, 30); border:2px solid transparent; border-radius:3px;}"
		"QScrollBar::handle:hover{background:rgb(20, 30, 15);border:3px solid transparent; border-radius:3px;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}"
		);

	//半透明
	//ui.result_table->setAttribute(Qt::WA_TranslucentBackground);
	ui.person_result_table->verticalHeader()->setDefaultSectionSize(50);
	ui.person_result_table->setTextElideMode(Qt::ElideNone);

	ui.person_result_table->setItemDelegate(new NoFocusDelegate());
	ui.person_result_table->setVisible(false);

	ui.person_pic_label->setPixmap(QPixmap(":/YouJoin/Resources/searchperson.png"));
	ui.person_pic_label->setVisible(false);

}

void YJ_Search_Bar::yj_init_connections()
{
	connect(ui.search_edit, SIGNAL(textChanged(const QString &)), this, SLOT(yj_search_trie(const QString &)));
}

void YJ_Search_Bar::yj_init_trie()
{
	yj_init_friend_trie();
	yj_init_music_trie();
}

void YJ_Search_Bar::yj_init_friend_trie()
{
	if (friendTrie != NULL){
		delete friendTrie;
		friendTrie = NULL;
	}

	friendTrie = new chTrieTree();
	friendTrie->insertChinese("-");
}

void YJ_Search_Bar::yj_init_music_trie()
{
	if (musicTrie != NULL){
		delete musicTrie;
		musicTrie = NULL;
	}

	musicTrie = new chTrieTree();
	musicTrie->insertChinese("-");
}
//  bool YJ_Search_Bar::eventFilter(QObject *obj, QEvent *e)
//  {
//  	if (obj == ui.search_edit || obj == ui.result_table){
//  		if (e->type() == QEvent::MouseButtonPress){
//  			emit YJ_Get_Focus();
// 			return QWidget::eventFilter(obj, e);
//  		}
//  		else {
//  			emit YJ_Lost_Focus();
// 			return QWidget::eventFilter(obj, e);
//  		}
//  	}
//  	return QWidget::eventFilter(obj, e);
//  	
//  }

void YJ_Search_Bar::YJ_set_music_list(QStringList list)
{
	yj_init_music_trie();
	musicContentList = list;
	for (int i = 0; i < musicContentList.size(); i++){
		QString temp = musicContentList.at(i);
		musicTrie->insertChinese(yj_qstring_to_gb2312(temp));
	}
}

void YJ_Search_Bar::YJ_set_friend_list(QStringList list)
{
	yj_init_friend_trie();
	friendContentList = list;
	for (int i = 0; i < friendContentList.size(); i++){
		QString temp = friendContentList.at(i);
		friendTrie->insertChinese(yj_qstring_to_gb2312(temp));
	}
}

char *YJ_Search_Bar::yj_qstring_to_gb2312(QString &str)
{
	QTextCodec *pCodec = QTextCodec::codecForName("GB2312");// "UTF-8", "UTF-16"
	QByteArray data = pCodec->fromUnicode(str);

	if (str.length() == 0) return "";

	char *result = new char[data.size() + 1];
	for (int i = 0; i < data.size(); i++){
		result[i] = data[i];
		result[i + 1] = 0;
	}

	return result;
}

void YJ_Search_Bar::yj_search_trie(const QString & str)
{
	QString temp = str;

	vector<string> musicResult = musicTrie->getPrefixWords(yj_qstring_to_gb2312(temp));
	// 	int a = allUserTrie->findChinese("梁宏学");
	// 	vector<string> result = allUserTrie->getPrefixWords("梁");
	musicResultList.clear();
	for (int i = 0; i < musicResult.size(); i++){
		QString s = QString::fromLocal8Bit(musicResult[i].c_str());
		musicResultList.append(s);
	}

	vector<string> friendResult = friendTrie->getPrefixWords(yj_qstring_to_gb2312(temp));
	friendResultList.clear();
	for (int i = 0; i < friendResult.size(); i++){
		QString s = QString::fromLocal8Bit(friendResult[i].c_str());
		friendResultList.append(s);
	}

	if (musicResultList.size() < 1 && friendResultList.size() < 1){
		ui.result_table->setVisible(false);
		ui.pic_label->setVisible(false);
		ui.person_pic_label->setVisible(false);
		ui.person_result_table->setVisible(false);
		return;
	}
	yj_update_music_table();
	yj_update_friend_table();
}

void YJ_Search_Bar::yj_update_music_table()
{
	ui.result_table->setVisible(true);
	ui.pic_label->setVisible(true);
	ui.person_pic_label->setVisible(true);
	ui.person_result_table->setVisible(true);

	ui.result_table->setRowCount(0);
	for (int i = 0; i < musicResultList.size(); i++){

		ui.result_table->insertRow(ui.result_table->rowCount());

		QTableWidgetItem *hehe = new QTableWidgetItem();

		//int id = userMap[resultList.at(i)];
		hehe->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 10));
		hehe->setText(musicResultList.at(i));

		ui.result_table->setItem(ui.result_table->rowCount() - 1, 0, hehe);

	}
}

void YJ_Search_Bar::yj_update_friend_table()
{
	ui.person_pic_label->setVisible(true);
	ui.person_result_table->setVisible(true);
	ui.result_table->setVisible(true);
	ui.pic_label->setVisible(true);

	ui.person_result_table->setRowCount(0);
	for (int i = 0; i < friendResultList.size(); i++){

		ui.person_result_table->insertRow(ui.person_result_table->rowCount());

		QTableWidgetItem *hehe = new QTableWidgetItem();

		//int id = userMap[resultList.at(i)];
		hehe->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 10));
		hehe->setText(friendResultList.at(i));

		ui.person_result_table->setItem(ui.person_result_table->rowCount() - 1, 0, hehe);

	}
}
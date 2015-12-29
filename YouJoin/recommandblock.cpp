#include "recommandblock.h"

YJ_Recommand_Block::YJ_Recommand_Block(QWidget *parent /* = 0 */)
: QWidget(parent)
{
	ui.setupUi(this);

	yj_init_ui();
	yj_init_connections();
}

void YJ_Recommand_Block::yj_init_ui()
{
	if (ui.friend_table->columnCount() < 1){
		ui.friend_table->setColumnCount(1);
		QTableWidgetItem *qtablewidgetitem1 = new QTableWidgetItem();
		ui.friend_table->setHorizontalHeaderItem(0, qtablewidgetitem1);
	}


	//�����п�
	ui.friend_table->setColumnWidth(0, 185);

	//��ֹ�༭��Ԫ������
	ui.friend_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//ѡ��һ��
	ui.friend_table->setSelectionMode(QAbstractItemView::NoSelection);
	//ȥ��ˮƽ������
	ui.friend_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//��ֱ�����������ƶ�
	ui.friend_table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	//ȥ��ˮƽ��ͷ
	ui.friend_table->horizontalHeader()->setFixedHeight(0);
	//ȥ����ֱ��ͷ
	ui.friend_table->verticalHeader()->setFixedWidth(0);
	//�����ޱ߿�
	ui.friend_table->setFrameShape(QFrame::NoFrame);
	//���ò���ʾ������
	ui.friend_table->setShowGrid(false);
	//�����Ҽ��˵�
	ui.friend_table->setContextMenuPolicy(Qt::CustomContextMenu);

	//���ñ�����ɫ
	QPalette pal;
	pal.setBrush(QPalette::Base, QBrush(QColor(0, 0, 0, 50)));
	ui.friend_table->setPalette(pal);

	//������ֱ��������ʽ
	ui.friend_table->setStyleSheet(
		"QScrollBar{ width: 5px;background-color: rgb(255, 255, 255);}"
		"QScrollBar::handle{background:rgb(35, 55, 30); border:2px solid transparent; border-radius:3px;}"
		"QScrollBar::handle:hover{background:rgb(20, 30, 15);border:3px solid transparent; border-radius:3px;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}"
		);


	//��͸��
	ui.friend_table->setAttribute(Qt::WA_TranslucentBackground);
	ui.friend_table->verticalHeader()->setDefaultSectionSize(50);
	ui.friend_table->setTextElideMode(Qt::ElideNone);

	ui.music_table->setItemDelegate(new NoFocusDelegate());

	if (ui.music_table->columnCount() < 1){
		ui.music_table->setColumnCount(1);
		QTableWidgetItem *qtablewidgetitem1 = new QTableWidgetItem();
		ui.music_table->setHorizontalHeaderItem(0, qtablewidgetitem1);
	}


	//�����п�
	ui.music_table->setColumnWidth(0, 283);

	//��ֹ�༭��Ԫ������
	ui.music_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//ѡ��һ��
	ui.music_table->setSelectionMode(QAbstractItemView::NoSelection);
	//ȥ��ˮƽ������
	ui.music_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//��ֱ�����������ƶ�
	ui.music_table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	//ȥ��ˮƽ��ͷ
	ui.music_table->horizontalHeader()->setFixedHeight(0);
	//ȥ����ֱ��ͷ
	ui.music_table->verticalHeader()->setFixedWidth(0);
	//�����ޱ߿�
	ui.music_table->setFrameShape(QFrame::NoFrame);
	//���ò���ʾ������
	ui.music_table->setShowGrid(false);
	//�����Ҽ��˵�
	ui.music_table->setContextMenuPolicy(Qt::CustomContextMenu);

	//���ñ�����ɫ
	QPalette pal2;
	pal2.setBrush(QPalette::Base, QBrush(QColor(0, 0, 0, 50)));
	ui.music_table->setPalette(pal2);

	//������ֱ��������ʽ
	ui.music_table->setStyleSheet(
		"QScrollBar{ width: 5px;background-color: rgb(255, 255, 255);}"
		"QScrollBar::handle{background:rgb(61, 11, 5); border:2px solid transparent; border-radius:3px;}"
		"QScrollBar::handle:hover{background:rgb(42, 9, 9);border:3px solid transparent; border-radius:3px;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}"
		"QTableWidget::item:selected { background-color: rgb(97, 17, 7) }"
		);


	//��͸��
	ui.music_table->setAttribute(Qt::WA_TranslucentBackground);
	ui.music_table->verticalHeader()->setDefaultSectionSize(50);
	ui.music_table->setTextElideMode(Qt::ElideNone);

	ui.music_table->setItemDelegate(new NoFocusDelegate());

	searchBar = new YJ_Search_Bar(this);
	searchBar->setGeometry(QRect(30, 23, 424, 41));
}

void YJ_Recommand_Block::yj_init_connections()
{
	connect(ui.friend_table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(yj_friend_table_item_dblclick(int, int)));
}


void YJ_Recommand_Block::YJ_set_musiclist(QStringList list)
{
	musicList = list;
	yj_update_music_table();
}

void YJ_Recommand_Block::YJ_set_friendlist(QList<user_info> list)
{
	friendlist = list;

	for (int i = 0; i < friendlist.size(); i++){
		friendList.append(friendlist.at(i).get_username());
	}

	yj_update_friend_table();
}

void YJ_Recommand_Block::yj_update_friend_table()
{
	foreach(QString fileName, friendList)
	{
		ui.friend_table->insertRow(ui.friend_table->rowCount());

		for (int i = 0; i < ui.friend_table->columnCount(); i++){
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setFont(QFont(QString::fromLocal8Bit("΢���ź�"), 11));
			item->setTextColor(QColor(194, 196, 208));

			ui.friend_table->setItem(ui.friend_table->rowCount() - 1, i, item);

		}
		ui.friend_table->item(ui.friend_table->rowCount() - 1, 0)->setText(fileName);

	}
	searchBar->YJ_set_friend_list(friendList);
	yj_set_friend_table_backgroud();
}

void YJ_Recommand_Block::yj_update_music_table()
{
	QStringList tempList;
	foreach(QString fileName, musicList)
	{
		ui.music_table->insertRow(ui.music_table->rowCount());

		for (int i = 0; i < ui.music_table->columnCount(); i++){
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setFont(QFont(QString::fromLocal8Bit("΢���ź�"), 11));
			item->setTextColor(QColor(194, 196, 208));

			ui.music_table->setItem(ui.music_table->rowCount() - 1, i, item);

		}
		QString name = QFileInfo(fileName).baseName();
		ui.music_table->item(ui.music_table->rowCount() - 1, 0)->setText(name);
		tempList.append(name);

	}
	searchBar->YJ_set_music_list(tempList);
	yj_set_music_table_background();
}

void YJ_Recommand_Block::yj_set_music_table_background()
{
	for (int i = 0; i < ui.music_table->rowCount(); i++){
		if (i % 2 == 0){
			for (int j = 0; j < ui.music_table->columnCount(); j++){
				QTableWidgetItem *item = ui.music_table->item(i, j);
				if (item){
					const QColor color = QColor(0, 0, 0, 50);
					item->setBackgroundColor(color);
				}
			}
		}
	}
}

void YJ_Recommand_Block::yj_set_friend_table_backgroud()
{
	for (int i = 0; i < ui.friend_table->rowCount(); i++){
		if (i % 2 == 0){
			for (int j = 0; j < ui.friend_table->columnCount(); j++){
				QTableWidgetItem *item = ui.friend_table->item(i, j);
				if (item){
					const QColor color = QColor(0, 0, 0, 50);
					item->setBackgroundColor(color);
				}
			}
		}
	}
}

void YJ_Recommand_Block::yj_friend_table_item_dblclick(int row, int column)
{
	if (row >= friendlist.size()) return;

	if (infoCard != NULL){
		delete infoCard;
		infoCard = NULL;
	}

	infoCard = new YJ_User_Info_Card(friendlist.at(row));
	connect(infoCard, SIGNAL(YJ_add_friend(int)), this, SIGNAL(YJ_add_friend(int)));
	infoCard->show();
}

void YJ_Recommand_Block::yj_add_friend(int userid)
{
	emit YJ_add_friend(userid);
}
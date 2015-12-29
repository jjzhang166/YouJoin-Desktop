#include "friendblock.h"

YJ_Friend_Block::YJ_Friend_Block(QWidget *parent /* = 0 */)
: QWidget(parent)
{
	ui.setupUi(this);
	yj_init_ui();
	yj_init_network();
	yj_init_connections();
	
}

YJ_Friend_Block::~YJ_Friend_Block()
{

}

void YJ_Friend_Block::yj_init_ui()
{
	QIcon icon_send_button;
	icon_send_button.addFile(":/YouJoin/Resources/send.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.send_button->setIcon(icon_send_button);
	ui.send_button->setFlat(true);
	ui.send_button->setFocusPolicy(Qt::NoFocus);
	ui.send_button->setIconSize(QSize(92, 88));

	if (ui.chat_table->columnCount() < 1)
		ui.chat_table->setColumnCount(3);
	QTableWidgetItem *qtablewidgetitem1 = new QTableWidgetItem();
	ui.chat_table->setHorizontalHeaderItem(0, qtablewidgetitem1);


	//�����п�
	ui.chat_table->setColumnWidth(0, 283);
	ui.chat_table->setColumnWidth(1, 30);
	ui.chat_table->setColumnWidth(2, 283);

	//��ֹ�༭��Ԫ������
	ui.chat_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//ѡ��һ��
	ui.chat_table->setSelectionMode(QAbstractItemView::NoSelection);
	//ȥ��ˮƽ������
	ui.chat_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//��ֱ�����������ƶ�
	ui.chat_table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	//ȥ��ˮƽ��ͷ
	ui.chat_table->horizontalHeader()->setFixedHeight(0);
	//ȥ����ֱ��ͷ
	ui.chat_table->verticalHeader()->setFixedWidth(0);
	//�����ޱ߿�
	ui.chat_table->setFrameShape(QFrame::NoFrame);
	//���ò���ʾ������
	ui.chat_table->setShowGrid(false);
	//�����Ҽ��˵�
	ui.chat_table->setContextMenuPolicy(Qt::CustomContextMenu);

	//���ñ�����ɫ
	QPalette pal;
	pal.setBrush(QPalette::Base, QBrush(QColor(0, 0, 0, 0)));
	ui.chat_table->setPalette(pal);

	//������ֱ��������ʽ
	ui.chat_table->setStyleSheet(
		"QScrollBar{ width: 5px;background-color: rgb(255, 255, 255);}"
		"QScrollBar::handle{background:rgb(35, 55, 30); border:2px solid transparent; border-radius:3px;}"
		"QScrollBar::handle:hover{background:rgb(20, 30, 15);border:3px solid transparent; border-radius:3px;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}"
	);

	//��͸��
	ui.chat_table->setAttribute(Qt::WA_TranslucentBackground);
	ui.chat_table->verticalHeader()->setDefaultSectionSize(50);
	ui.chat_table->setTextElideMode(Qt::ElideNone);

	



 	if (ui.friend_list_table->columnCount() < 1)
 		ui.friend_list_table->setColumnCount(1);
 	QTableWidgetItem *qtablewidgetitem2 = new QTableWidgetItem();
 	ui.friend_list_table->setHorizontalHeaderItem(0, qtablewidgetitem2);
 
 
 	//�����п�
 	ui.friend_list_table->setColumnWidth(0, 169);
 
 	//��ֹ�༭��Ԫ������
 	ui.friend_list_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
 	//ѡ��һ��
 	ui.friend_list_table->setSelectionMode(QAbstractItemView::NoSelection);
 	//ȥ��ˮƽ������
 	ui.friend_list_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
 	//��ֱ�����������ƶ�
 	ui.friend_list_table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
 	//ȥ��ˮƽ��ͷ
 	ui.friend_list_table->horizontalHeader()->setFixedHeight(0);
 	//ȥ����ֱ��ͷ
 	ui.friend_list_table->verticalHeader()->setFixedWidth(0);
 	//�����ޱ߿�
 	ui.friend_list_table->setFrameShape(QFrame::NoFrame);
 	//���ò���ʾ������
 	ui.friend_list_table->setShowGrid(false);
 	//�����Ҽ��˵�
 	ui.friend_list_table->setContextMenuPolicy(Qt::CustomContextMenu);
 
 	//���ñ�����ɫ
 	QPalette pal2;
 	pal2.setBrush(QPalette::Base, QBrush(QColor(0, 0, 0, 50)));
 	ui.friend_list_table->setPalette(pal2);
 
 	//������ֱ��������ʽ
 	ui.friend_list_table->setStyleSheet(
 		"QScrollBar{ width: 3px;background-color: rgb(220, 90, 65);}"
 		"QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:3px;}"
 		"QScrollBar::handle:hover{background:white;border:3px solid transparent; border-radius:3px;}"
 		"QScrollBar::sub-line{background:transparent;}"
 		"QScrollBar::add-line{background:transparent;}"
 		);
 
 
 	//��͸��
	ui.friend_list_table->setAttribute(Qt::WA_TranslucentBackground);
	ui.friend_list_table->verticalHeader()->setDefaultSectionSize(50);
	ui.friend_list_table->setTextElideMode(Qt::ElideNone);
 
 	ui.friend_list_table->setItemDelegate(new NoFocusDelegate());
	ui.chat_table->setItemDelegate(new NoFocusDelegate());

	receive_brush = new QBrush(QPixmap(":/YouJoin/Resources/text-receive.png"));
	send_brush = new QBrush(QPixmap(":/YouJoin/Resources/text-send.png"));


// 	QPalette pl = ui.msg_edit->palette();
// 
// 	pl.setBrush(QPalette::Base, QBrush(QColor(255, 0, 0, 0)));
// 
// 	ui.msg_edit->setPalette(pl);

	ui.msg_edit->installEventFilter(this);

}

bool YJ_Friend_Block::eventFilter(QObject *obj, QEvent *e)
{
	if (obj == ui.msg_edit && e->type() == QEvent::KeyPress){
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
		if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return){
			yj_send_button_clicked();
			return true;
		}
	}

	return QWidget::eventFilter(obj, e);
}

void YJ_Friend_Block::yj_init_network()
{
	UdpSender = new QUdpSocket(this);
	UdpReader = new QUdpSocket(this);

	UdpReader->bind(YJ_CONSTANTS::PORT_CHAT_RECEIVE, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
	connect(UdpReader, SIGNAL(readyRead()), this, SLOT(yj_receive_msg()));
}

void YJ_Friend_Block::yj_init_connections()
{
	connect(ui.send_button, SIGNAL(clicked()), this, SLOT(yj_send_button_clicked()));
	connect(ui.friend_list_table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(yj_friend_table_item_dblclick(int, int)));
}

void YJ_Friend_Block::yj_receive_msg()
{
	int sender;
	int receiver;
	QString msg;
	while (UdpReader->hasPendingDatagrams()){
		QByteArray datagram;
		datagram.resize(UdpReader->pendingDatagramSize());
		UdpReader->readDatagram(datagram.data(), datagram.size());
		receivemsg = datagram;
		QJsonDocument jsonDocument = QJsonDocument::fromJson(receivemsg.toUtf8());
		QVariantList list = jsonDocument.toVariant().toList();
		if (list.size() < 1) continue;
		QVariantMap msg_map = list.at(0).toMap();

		sender = msg_map[QLatin1Literal("sender")].toInt();
		receiver = msg_map[QLatin1Literal("receiver")].toInt();
		msg = msg_map[QLatin1Literal("msg")].toString();
	}

	if (sender == info.get_user_id() || receiver != info.get_user_id()) return;

	ui.chat_table->insertRow(ui.chat_table->rowCount());
	ui.chat_table->setRowHeight(ui.chat_table->rowCount() - 1, 80);

	for (int i = 0; i < ui.chat_table->columnCount(); i++)
	{
		QTableWidgetItem *item = new QTableWidgetItem;


		if (i == 0){
			item->setBackground(*receive_brush);
			item->setTextAlignment(Qt::AlignCenter);
			item->setFont(QFont(QString::fromLocal8Bit("΢���ź�"), 12));
			item->setTextColor(QColor(255, 255, 255));
		}
		ui.chat_table->setItem(ui.chat_table->rowCount() - 1, i, item);

	}

	ui.chat_table->item(ui.chat_table->rowCount() - 1, 0)->setText(msg);
}

void YJ_Friend_Block::yj_send_msg(QString &msg)
{
	localmsg = msg;

	QVariantMap str_map;
	QJsonDocument jsonDocument;

	str_map.insert("sender", info.get_user_id());
	str_map.insert("receiver", now_chat_userid);
	str_map.insert("msg", msg);

	QVariantList list;
	list << str_map;

	jsonDocument = QJsonDocument::fromVariant(list);
	localmsg = jsonDocument.toJson();

	QByteArray datagram = localmsg.toUtf8();
	UdpSender->writeDatagram(datagram.data(), datagram.size(), 
		QHostAddress::Broadcast, YJ_CONSTANTS::PORT_CHAT_RECEIVE);

	ui.chat_table->insertRow(ui.chat_table->rowCount());
	ui.chat_table->setRowHeight(ui.chat_table->rowCount() - 1, 80);
	
	for (int i = 0; i < ui.chat_table->columnCount(); i++)
	{
		QTableWidgetItem *item = new QTableWidgetItem;

		if (i == 2){
			item->setBackground(*send_brush);
			item->setTextAlignment(Qt::AlignCenter);
			item->setFont(QFont(QString::fromLocal8Bit("΢���ź�"), 12));
			item->setTextColor(QColor(255, 255, 255));
		}
		ui.chat_table->setItem(ui.chat_table->rowCount() - 1, i, item);

	}

	ui.chat_table->item(ui.chat_table->rowCount() - 1, 2)->setText(msg);
	 
}

void YJ_Friend_Block::yj_send_button_clicked()
{
	QString msg = ui.msg_edit->toPlainText();
	if (msg == "") return;
	
	yj_send_msg(msg);
	ui.msg_edit->clear();
}

void YJ_Friend_Block::YJ_set_userinfo(user_info u, const vector<user_info> &friendlist)
{
	info = u;
	friends = friendlist;
	yj_refresh_friend_table();
}

void YJ_Friend_Block::yj_refresh_friend_table()
{
	QStringList friendList;

	for (int i = 0; i < friends.size(); i++){
		friendList.append(friends.at(i).get_username());
	}

	ui.friend_list_table->setRowCount(0);
	
	foreach(QString fileName, friendList)
	{
		ui.friend_list_table->insertRow(ui.friend_list_table->rowCount());

		for (int i = 0; i < ui.friend_list_table->columnCount(); i++){
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setFont(QFont(QString::fromLocal8Bit("΢���ź�"), 11));
			item->setTextColor(QColor(194, 196, 208));

			ui.friend_list_table->setItem(ui.friend_list_table->rowCount() - 1, i, item);

		}
		ui.friend_list_table->item(ui.friend_list_table->rowCount() - 1, 0)->setText(fileName);

	}

	yj_set_friend_table_backgroud();
}

void YJ_Friend_Block::yj_set_friend_table_backgroud()
{
	for (int i = 0; i < ui.friend_list_table->rowCount(); i++){
		if (now_row == i){
			QTableWidgetItem *item = ui.friend_list_table->item(i, 0);
			if (item){
				QColor color = QColor(20, 30, 15);
				item->setBackgroundColor(color);
			}
			continue;
		}
		if (i % 2 == 0){
			QTableWidgetItem *item = ui.friend_list_table->item(i, 0);
			if (item){
				QColor color = QColor(0, 0, 0, 50);
				item->setBackgroundColor(color);
			}
		}
		else{
			QTableWidgetItem *item = ui.friend_list_table->item(i, 0);
			if (item){
				QColor color = QColor(0, 0, 0, 0);
				item->setBackgroundColor(color);
			}
		}

	}
}

void YJ_Friend_Block::yj_friend_table_item_dblclick(int row, int column)
{
	if (row >= friends.size()) return;

	user_info temp = friends.at(row);

	now_chat_userid = temp.get_user_id();

	ui.chat_table->setRowCount(0);

	now_row = row;

	yj_set_friend_table_backgroud();

}

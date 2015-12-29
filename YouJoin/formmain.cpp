#include "formmain.h"

YJ_Main_Form::YJ_Main_Form(QWidget *parent /* = 0 */)
: QWidget(parent)
{
	ui.setupUi(this);
	yj_init_metadata();
	yj_init_ui();
	yj_init_connections();

}

YJ_Main_Form::~YJ_Main_Form()
{
	yj_delete_all_pages();
	if (sidebar != NULL) delete sidebar;
	if (userblock != NULL) delete userblock;
	if (weatherblock != NULL) delete weatherblock;
	if (infocollectionform != NULL) delete infocollectionform;
	if (moreblock != NULL) delete moreblock;
	if (recommandBlock != NULL) delete recommandBlock;
}

void YJ_Main_Form::yj_init_metadata()
{

	background_group[HOMEPAGE] = ":/YouJoin/Resources/homepage-background.png";
	background_group[FRIEND] = ":/YouJoin/Resources/friend-background.png";
	background_group[RECOMMEND] = ":/YouJoin/Resources/recommand-background.png";
	background_group[PHOTO] = ":/YouJoin/Resources/photo-background.png";
	background_group[MUSIC] = ":/YouJoin/Resources/music-background.png";
	background_group[VIDEO] = ":/YouJoin/Resources/information-background.png";
	background_group[MORE] = ":/YouJoin/Resources/more-background.png";

	background_pic = background_group[HOMEPAGE];

}

void YJ_Main_Form::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.drawPixmap(0, 0, QPixmap(background_pic));
}

void YJ_Main_Form::yj_init_ui()
{
	//去除标题栏
	this->setWindowFlags(Qt::FramelessWindowHint);
	//窗口拖动
	QWidgetResizeHandler *movewin = new QWidgetResizeHandler(this);
	movewin->setMovingEnabled(true);
	//固定大小
	this->setFixedSize(1025, 600);
	//背景透明
	setAttribute(Qt::WA_TranslucentBackground);
	//半透明
	//this->setWindowOpacity(0.9);

	if (ui.msgTable->columnCount() < 1)
		ui.msgTable->setColumnCount(1);
	QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
	ui.msgTable->setHorizontalHeaderItem(0, __qtablewidgetitem);


	//设置列宽
	ui.msgTable->setColumnWidth(0, 571);
	
	//ui.msgTable->setColumnWidth(1, 100);

	//禁止编辑单元格内容
	ui.msgTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//选中一行
	ui.msgTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//去掉水平滚动条
	ui.msgTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//垂直滚动条按项移动
	ui.msgTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	//去除水平表头
	ui.msgTable->horizontalHeader()->setFixedHeight(0);
	//去除垂直表头
	ui.msgTable->verticalHeader()->setFixedWidth(0);
	//设置无边框
	ui.msgTable->setFrameShape(QFrame::NoFrame);
	//设置不显示格子线
	ui.msgTable->setShowGrid(false);
	//设置右键菜单
	ui.msgTable->setContextMenuPolicy(Qt::CustomContextMenu);

	//设置背景颜色
	QPalette pal;
	pal.setBrush(QPalette::Base, QBrush(QColor(0, 0, 0, 0)));
	ui.msgTable->setPalette(pal);

	//设置竖直滚动条样式
	ui.msgTable->setStyleSheet(
		"QScrollBar{ width: 5px;background-color: rgb(255, 255, 255);}"
		"QScrollBar::handle{background:rgb(61, 150, 250); border:2px solid transparent; border-radius:3px;}"
		"QScrollBar::handle:hover{background:rgb(1, 89, 179);border:3px solid transparent; border-radius:3px;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}");
	//半透明
	ui.msgTable->setAttribute(Qt::WA_TranslucentBackground);
	ui.msgTable->verticalHeader()->setDefaultSectionSize(50);
	ui.msgTable->setTextElideMode(Qt::ElideNone);

	ui.msgTable->setItemDelegate(new NoFocusDelegate());


	QPalette pl = ui.msgEdit->palette();

	pl.setBrush(QPalette::Base, QBrush(QColor(255, 0, 0, 0)));

	ui.msgEdit->setPalette(pl);
	//ui.msgEdit->setStyleSheet("background-image: url(:/YouJoin/Resources/homepage-send.png)");

	//ui.msgEdit->setHtml("<body   background=\"./YouJoin/Resources/homepage-send.png\"> </body>");

	QIcon icon_send_button;
	icon_send_button.addFile(":/YouJoin/Resources/homepage-send.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.send_buttton->setIcon(icon_send_button);
	ui.send_buttton->setFlat(true);
	ui.send_buttton->setFocusPolicy(Qt::NoFocus);
	ui.send_buttton->setIconSize(QSize(71, 162));

	msgtable_item = new QBrush(QPixmap(":/YouJoin/Resources/homepage-msg.png"));

	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("MM-dd");
	ui.date_label->setText(current_date);
	ui.date_label->setWordWrap(true);
	ui.date_label->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 14));
	ui.date_label->setStyleSheet("color:white;");

	sidebar = new YJ_Sidebar(this);
	sidebar->setGeometry(QRect(0, 0, 200, 600));

	userblock = new YJ_User_Block(true, QString("zzq"), this);
	userblock->setGeometry(QRect(10, 10, 157, 75));

	weatherblock = new YJ_Weather_Block(this);
	weatherblock->setGeometry(QRect(837, 60, 176, 56));

	musicblock = NULL;
	friendblock = NULL;
	infocollectionform = NULL;

	musicblock = new YJ_Music_Block(this);
	musicblock->setGeometry(QRect(200, 0, 825, 600));
	musicblock->setVisible(false);

 	friendblock = new YJ_Friend_Block(this);
 	friendblock->setGeometry(QRect(200, 0, 825, 600));
 	friendblock->setVisible(false);

	infocollectionform = new YJ_InfoCollection_Form(this);
	infocollectionform->setGeometry(QRect(200, 0, 825, 600));
	infocollectionform->setVisible(false);

	moreblock = new YJ_More_Block(this);
	moreblock->setGeometry(QRect(200, 0, 825, 600));
	moreblock->setVisible(false);
	connect(moreblock, SIGNAL(YJ_show_self()), this, SLOT(yj_show_self()));
	connect(moreblock, SIGNAL(YJ_quit()), this, SLOT(yj_quit()));

	recommandBlock = new YJ_Recommand_Block(this);
	recommandBlock->setGeometry(QRect(200, 0, 825, 600));
	recommandBlock->setVisible(false);
	connect(recommandBlock, SIGNAL(YJ_add_friend(int)), this, SIGNAL(YJ_add_friend(int)));

	photoblock = new YJ_Photo_Block(this);
	photoblock->setGeometry(QRect(200, 0, 825, 600));
	photoblock->setVisible(false);
}

void YJ_Main_Form::yj_init_connections()
{
	connect(sidebar, SIGNAL(yj_homepage_button_clicked(int)), this, SLOT(yj_cut_page(int)));
	connect(sidebar, SIGNAL(yj_friend_button_clicked(int)), this, SLOT(yj_cut_page(int)));
	connect(sidebar, SIGNAL(yj_recommend_button_clicked(int)), this, SLOT(yj_cut_page(int)));
	connect(sidebar, SIGNAL(yj_photo_button_clicked(int)), this, SLOT(yj_cut_page(int)));
	connect(sidebar, SIGNAL(yj_music_button_clicked(int)), this, SLOT(yj_cut_page(int)));
	connect(sidebar, SIGNAL(yj_video_button_clicked(int)), this, SLOT(yj_cut_page(int)));
	connect(sidebar, SIGNAL(yj_more_button_clicked(int)), this, SLOT(yj_cut_page(int)));
	connect(infocollectionform, SIGNAL(YJ_Detail_Update()), this, SLOT(yj_update_detail()));
	connect(ui.send_buttton, SIGNAL(clicked()), this, SLOT(yj_send_button_clicked()));

	connect(musicblock, SIGNAL(YJ_Music_List_Changed()), this, SLOT(yj_refresh_musiclist()));
	
}

void YJ_Main_Form::YJ_set_background(QString &pic)
{
	background_pic = pic;
	this->update();
}

void YJ_Main_Form::yj_page_to_homepage()
{
	YJ_set_background(background_group[HOMEPAGE]);
	yj_visiable_main_page();
}

void YJ_Main_Form::yj_page_to_friend()
{
	YJ_set_background(background_group[FRIEND]);
	if (friendblock == NULL){
		friendblock = new YJ_Friend_Block(this);
		friendblock->setGeometry(QRect(200, 0, 825, 600));
	}

	friendblock->setVisible(true);
}

void YJ_Main_Form::yj_page_to_recommend()
{
	YJ_set_background(background_group[RECOMMEND]);
	if (recommandBlock == NULL){
		recommandBlock = new YJ_Recommand_Block(this);
		recommandBlock->setGeometry(QRect(200, 0, 825, 600));
	}

	recommandBlock->setVisible(true);
}

void YJ_Main_Form::yj_page_to_photo()
{
	YJ_set_background(background_group[PHOTO]);

	if (photoblock == NULL){
		photoblock = new YJ_Photo_Block(this);
		photoblock->setGeometry(QRect(200, 0, 825, 600));
	}

	photoblock->setVisible(true);
}

void YJ_Main_Form::yj_page_to_music()
{
	YJ_set_background(background_group[MUSIC]);
	if (musicblock == NULL){
		musicblock = new YJ_Music_Block(this);
		musicblock->setGeometry(QRect(200, 0, 825, 600));
	}

	musicblock->setVisible(true);
}

void YJ_Main_Form::yj_page_to_video()
{
	YJ_set_background(background_group[VIDEO]);
	if (infocollectionform == NULL){
		infocollectionform = new YJ_InfoCollection_Form(this);
		infocollectionform->setGeometry(QRect(200, 0, 825, 600));
	}

	infocollectionform->setVisible(true);
}

void YJ_Main_Form::yj_page_to_more()
{
	YJ_set_background(background_group[MORE]);
	if (moreblock == NULL){
		moreblock = new YJ_More_Block(this);
		moreblock->setGeometry(QRect(200, 0, 825, 600));
	}
	moreblock->setVisible(true);
}

void YJ_Main_Form::yj_cut_page(int button_flag)
{
	yj_invisiable_all_pages();
	switch (button_flag){
	case HOMEPAGE:
		yj_page_to_homepage();
		break;
	case FRIEND:
		yj_page_to_friend();
		break;
	case RECOMMEND:
		yj_page_to_recommend();
		break;
	case PHOTO:
		yj_page_to_photo();
		break;
	case MUSIC:
		yj_page_to_music();
		break;
	case VIDEO:
		yj_page_to_video();
		break;
	case MORE:
		yj_page_to_more();
		break;
	default:

		break;
	}
}

void YJ_Main_Form::yj_delete_all_pages()
{
	if (musicblock != NULL){
		delete musicblock;
		musicblock = NULL;
	}
		
	if (friendblock != NULL){
		delete friendblock;
		friendblock = NULL;
	}

	if (infocollectionform != NULL){
		delete infocollectionform;
		infocollectionform = NULL;
	}

	if (moreblock != NULL){
		delete moreblock;
		moreblock = NULL;
	}

	if (recommandBlock != NULL){
		delete recommandBlock;
		recommandBlock = NULL;
	}

	if (photoblock != NULL){
		delete photoblock;
		photoblock = NULL;
	}
	
}

void YJ_Main_Form::yj_invisiable_all_pages()
{
	if (musicblock != NULL){
		musicblock->setVisible(false);
	}
	if (friendblock != NULL){
		friendblock->setVisible(false);
	}
	if (infocollectionform != NULL){
		infocollectionform->setVisible(false);
	}
	if (moreblock != NULL){
		moreblock->setVisible(false);
	}
	if (recommandBlock != NULL){
		recommandBlock->setVisible(false);
	}
	if (photoblock != NULL){
		photoblock->setVisible(false);
	}
	yj_invisiable_main_page();
}

void YJ_Main_Form::YJ_set_user(user_info user, const vector<user_info> &friendlist)
{
	info = user;
	friends = friendlist;
	userblock->YJ_set_username(info.get_username());

	if (friendblock != NULL) friendblock->YJ_set_userinfo(user, friends);
	if (infocollectionform != NULL) infocollectionform->setDetail(*info.get_detail());
}

void YJ_Main_Form::yj_update_detail()
{
	yj_set_detail(infocollectionform->getDetail());
	emit YJ_Detail_Update();
}

void YJ_Main_Form::yj_set_detail(user_detail detail)
{
	info.set_detail(&detail);
}

user_info YJ_Main_Form::YJ_get_user_info()
{
	return info;
}

user_detail YJ_Main_Form::YJ_get_user_detail()
{
	user_detail res(info.get_detail()->toVariantMap());
	return res;
}

void YJ_Main_Form::yj_refresh_musiclist()
{
	if (recommandBlock != NULL && musicblock != NULL){
		recommandBlock->YJ_set_musiclist(musicblock->YJ_Get_Music_List());
	}
}

void YJ_Main_Form::YJ_set_recommand_list(QList<user_info> list)
{
	recommandBlock->YJ_set_friendlist(list);
}

void YJ_Main_Form::yj_show_self()
{
	if (infoCard != NULL){
		delete infoCard;
		infoCard = NULL;
	}

	infoCard = new YJ_User_Info_Card(info, this, false);
	infoCard->show();
}

void YJ_Main_Form::yj_invisiable_main_page()
{
	weatherblock->setVisible(false);
	ui.send_buttton->setVisible(false);
	ui.msgEdit->setVisible(false);
	ui.msgTable->setVisible(false);
	ui.date_label->setVisible(false);
}

void YJ_Main_Form::yj_visiable_main_page()
{
	weatherblock->setVisible(true);
	ui.send_buttton->setVisible(true);
	ui.msgEdit->setVisible(true);
	ui.msgTable->setVisible(true);
	ui.date_label->setVisible(true);

}

void YJ_Main_Form::yj_quit()
{
	this->close();
}

void YJ_Main_Form::yj_send_button_clicked()
{
	QString text = ui.msgEdit->toPlainText();
	if (text.size() == 0) return;

	emit YJ_push_public_msg(text);

	//这里添加将新消息加入table的函数
	msgList.append(text);
	yj_add_msg_table();
	ui.msgEdit->setText("");
}

void YJ_Main_Form::YJ_receive_msg(QVariantMap result)
{
	int getDataType = result[QLatin1Literal("type")].toInt();
	int userid = result[QLatin1Literal("id")].toInt();
	QString text = result[QLatin1Literal("msg")].toString();

	//只显示好友发送的动态
	bool is_show = false;
	for (int i = 0; i < friends.size(); i++){
		if (friends.at(i).get_user_id() == userid) 
			is_show = true;
	}

	if (!is_show || userid == info.get_user_id()) return;

	msgList.append(text);
	yj_add_msg_table();
}

void YJ_Main_Form::yj_add_msg_table()
{
	ui.msgTable->setRowCount(0);
	for (int j = msgList.size() - 1; j >= 0; j--){
		QString msg = msgList.at(j);
		ui.msgTable->insertRow(ui.msgTable->rowCount());
		ui.msgTable->setRowHeight(ui.msgTable->rowCount() - 1, 80);

		for (int i = 0; i < ui.msgTable->columnCount(); i++){
			QTableWidgetItem *item = new QTableWidgetItem;
			if (i == 0){
				item->setBackground(*msgtable_item);
				item->setTextAlignment(Qt::AlignCenter);
				item->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 12));
				item->setTextColor(QColor(255, 255, 255));
			}
			ui.msgTable->setItem(ui.msgTable->rowCount() - 1, i, item);

		}
		ui.msgTable->setRowHeight(ui.msgTable->rowCount() - 1, 135);
		ui.msgTable->item(ui.msgTable->rowCount() - 1, 0)->setText(msg);
	}

}
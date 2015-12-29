#include "sidebar.h"

YJ_Sidebar::YJ_Sidebar(QWidget *parent /* = 0 */) 
: QWidget(parent)
{
	ui.setupUi(this);
	yj_init_button_info();
	yj_init_ui();
	yj_init_connections();
}

YJ_Sidebar::~YJ_Sidebar()
{

}

void YJ_Sidebar::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.drawPixmap(0, 0, QPixmap(":/YouJoin/Resources/sidebar_background.png"));

}

void YJ_Sidebar::yj_init_ui()
{
	//去除标题栏
	this->setWindowFlags(Qt::FramelessWindowHint);
	//固定大小
	this->setFixedSize(200, 600);
	//背景透明
	setAttribute(Qt::WA_TranslucentBackground);

	QIcon icon_temp;
	icon_temp.addFile(":/YouJoin/Resources/homepage-click.png", QSize(), QIcon::Normal, QIcon::Off);

	QIcon icon_temp_push;
	icon_temp_push.addFile(":/YouJoin/Resources/homepage-click.png", QSize(), QIcon::Normal, QIcon::Off);
	button_group[HOMEPAGE].name->Set_Button_Icons(icon_temp, icon_temp, icon_temp);
	button_group[HOMEPAGE].name->setFlat(true);
	button_group[HOMEPAGE].name->setFocusPolicy(Qt::NoFocus);
	button_group[HOMEPAGE].name->setIconSize(QSize(200, 58));
	button_group[HOMEPAGE].name->setGeometry(QRect(0, (132 + 58 * 0), 200, 58));
	
	for (int i = 1; i < 7; i++){
		QIcon icon_temp;
		icon_temp.addFile(button_group[i].unpushed_icon, QSize(), QIcon::Normal, QIcon::Off);
		QIcon icon_temp_push;
		icon_temp_push.addFile(button_group[i].pushed_icon, QSize(), QIcon::Normal, QIcon::Off);

		button_group[i].name->Set_Button_Icons(icon_temp, icon_temp, icon_temp);
		button_group[i].name->setFlat(true);
		button_group[i].name->setFocusPolicy(Qt::NoFocus);
		button_group[i].name->setIconSize(QSize(179, 58));
		button_group[i].name->setGeometry(QRect(0, (132 + 58 * i), 179, 58));
	}
}

void YJ_Sidebar::yj_init_connections()
{
	connect(button_group[HOMEPAGE].name, SIGNAL(clicked()), this, SLOT(yj_homepage_button_click()));
	connect(button_group[FRIEND].name, SIGNAL(clicked()), this, SLOT(yj_friend_button_click()));
	connect(button_group[RECOMMEND].name, SIGNAL(clicked()), this, SLOT(yj_recommend_button_click()));
	connect(button_group[PHOTO].name, SIGNAL(clicked()), this, SLOT(yj_photo_button_click()));
	connect(button_group[MUSIC].name, SIGNAL(clicked()), this, SLOT(yj_music_button_click()));
	connect(button_group[VIDEO].name, SIGNAL(clicked()), this, SLOT(yj_video_button_click()));
	connect(button_group[MORE].name, SIGNAL(clicked()), this, SLOT(yj_more_button_click()));
}

void YJ_Sidebar::yj_init_button_info()
{
	//button_group[HOMEPAGE].name = ui.homepage_button;
	//button_group[FRIEND].name = ui.friend_button;
	//button_group[RECOMMEND].name = ui.recommend_button;
	//button_group[PHOTO].name = ui.photo_button;
	//button_group[MUSIC].name = ui.music_button;
	//button_group[VIDEO].name = ui.video_button;
	//button_group[MORE].name = ui.more_button;

	button_group[HOMEPAGE].name = new I_PushButton(this);
	button_group[FRIEND].name = new I_PushButton(this);
	button_group[RECOMMEND].name = new I_PushButton(this);
	button_group[PHOTO].name = new I_PushButton(this);
	button_group[MUSIC].name = new I_PushButton(this);
	button_group[VIDEO].name = new I_PushButton(this);
	button_group[MORE].name = new I_PushButton(this);

	for (int i = 0; i < 7; i++){
		button_group[i].state = false;
	}
	button_group[HOMEPAGE].state = true;

	button_group[HOMEPAGE].pushed_icon = ":/YouJoin/Resources/homepage-click.png";
	button_group[FRIEND].pushed_icon = ":/YouJoin/Resources/friend-click.png";
	button_group[RECOMMEND].pushed_icon = ":/YouJoin/Resources/recommend-click.png";
	button_group[PHOTO].pushed_icon = ":/YouJoin/Resources/photo-click.png";
	button_group[MUSIC].pushed_icon = ":/YouJoin/Resources/music-click.png";
	button_group[VIDEO].pushed_icon = ":/YouJoin/Resources/information-click.png";
	button_group[MORE].pushed_icon = ":/YouJoin/Resources/more-click.png";
	
	button_group[HOMEPAGE].unpushed_icon = ":/YouJoin/Resources/homepage-notclick.png";
	button_group[FRIEND].unpushed_icon = ":/YouJoin/Resources/friend-notclick.png";
	button_group[RECOMMEND].unpushed_icon = ":/YouJoin/Resources/recommend-notclick.png";
	button_group[PHOTO].unpushed_icon = ":/YouJoin/Resources/photo-notclick.png";
	button_group[MUSIC].unpushed_icon = ":/YouJoin/Resources/music-notclick.png";
	button_group[VIDEO].unpushed_icon = ":/YouJoin/Resources/information-notclick.png";
	button_group[MORE].unpushed_icon = ":/YouJoin/Resources/more-notclick.png";

}

int YJ_Sidebar::yj_get_pushed_button()
{
	int button_flag = -1;
	for (int i = 0; i < 7; i++){
		if (button_group[i].state){
			button_flag = i;
			break;
		}
	}

	return button_flag;
}

void YJ_Sidebar::yj_set_pushed_button(int button_flag)
{
	if (button_flag == yj_get_pushed_button()) return;

	if (button_flag != -1) yj_set_unpushed_button(yj_get_pushed_button());

	button_group[button_flag].state = true;

	QIcon icon_temp;
	icon_temp.addFile(button_group[button_flag].pushed_icon, 
		QSize(), QIcon::Normal, QIcon::Off);

	button_group[button_flag].name->Set_Button_Icons(icon_temp, icon_temp, icon_temp);
	button_group[button_flag].name->setFlat(true);
	button_group[button_flag].name->setFocusPolicy(Qt::NoFocus);
	button_group[button_flag].name->setIconSize(QSize(200, 58));
	button_group[button_flag].name->setGeometry(QRect(0, (132 + 58 * button_flag), 200, 58));

}

void YJ_Sidebar::yj_set_unpushed_button(int button_flag)
{
	if (button_group[button_flag].state == false) return;

	button_group[button_flag].state = false;

	QIcon icon_temp;
	icon_temp.addFile(button_group[button_flag].unpushed_icon, 
		QSize(), QIcon::Normal, QIcon::Off);
	button_group[button_flag].name->Set_Button_Icons(icon_temp, icon_temp, icon_temp);
	button_group[button_flag].name->setFlat(true);
	button_group[button_flag].name->setFocusPolicy(Qt::NoFocus);
	button_group[button_flag].name->setIconSize(QSize(179, 58));
	button_group[button_flag].name->setGeometry(QRect(0, (132 + 58 * button_flag), 179, 58));
}

void YJ_Sidebar::yj_homepage_button_click()
{
	yj_set_pushed_button(HOMEPAGE);
	emit yj_homepage_button_clicked(HOMEPAGE);
}
void YJ_Sidebar::yj_friend_button_click()
{
	yj_set_pushed_button(FRIEND);
	emit yj_friend_button_clicked(FRIEND);
}
void YJ_Sidebar::yj_recommend_button_click()
{
	yj_set_pushed_button(RECOMMEND);
	emit yj_recommend_button_clicked(RECOMMEND);
}
void YJ_Sidebar::yj_photo_button_click()
{
	yj_set_pushed_button(PHOTO);
	emit yj_photo_button_clicked(PHOTO);
}
void YJ_Sidebar::yj_music_button_click()
{
	yj_set_pushed_button(MUSIC);
	emit yj_music_button_clicked(MUSIC);
}
void YJ_Sidebar::yj_video_button_click()
{
	yj_set_pushed_button(VIDEO);
	emit yj_video_button_clicked(VIDEO);
}
void YJ_Sidebar::yj_more_button_click()
{
	yj_set_pushed_button(MORE);
	emit yj_more_button_clicked(MORE);
}
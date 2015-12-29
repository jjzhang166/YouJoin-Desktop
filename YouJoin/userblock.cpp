#include "userblock.h"

YJ_User_Block::YJ_User_Block(bool state, QString user, QWidget *parent /* = 0 */)
: QWidget(parent)
{
	ui.setupUi(this);
	yj_init_info(state, user);
	yj_init_ui();
	yj_init_connection();
}

YJ_User_Block::~YJ_User_Block()
{

}

void YJ_User_Block::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.drawPixmap(0, 0, QPixmap(":/YouJoin/Resources/userblock-background.png"));
}

void YJ_User_Block::yj_init_ui()
{
	//去除标题栏
	this->setWindowFlags(Qt::FramelessWindowHint);
	//固定大小
	this->setFixedSize(157, 75);
	//背景透明
	setAttribute(Qt::WA_TranslucentBackground);

	QIcon icon_button;
	icon_button.addFile(QStringLiteral(":/YouJoin/Resources/online-button.png"), QSize(), QIcon::Normal, QIcon::Off);
	ui.state_cut_button->setIcon(icon_button);
	ui.state_cut_button->setFlat(true);
	ui.state_cut_button->setFocusPolicy(Qt::NoFocus);
	ui.state_cut_button->setIconSize(QSize(60, 18));

	ui.username_label->setWordWrap(true);
	ui.username_label->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 13));
	//ui.username_label->setStyleSheet("color:lightgray;");

	ui.pic_label->setPixmap(QPixmap(":/YouJoin/Resources/user.png"));
	
}

void YJ_User_Block::yj_init_connection()
{
	connect(ui.state_cut_button, SIGNAL(clicked()), this, SLOT(yj_statecut_button_click()));
}

void YJ_User_Block::yj_init_info(bool state, QString user)
{
	YJ_set_button_state(state);
	YJ_set_username(user);
}

void YJ_User_Block::yj_statecut_button_click()
{
	QIcon icon_button;
	if (button_state) {
		button_state = false;
		
		icon_button.addFile(QStringLiteral(":/YouJoin/Resources/offline-button.png"), QSize(), QIcon::Normal, QIcon::Off);
		ui.state_cut_button->setIcon(icon_button);
	}
	else{
		button_state = true;

		icon_button.addFile(QStringLiteral(":/YouJoin/Resources/online-button.png"), QSize(), QIcon::Normal, QIcon::Off);
		ui.state_cut_button->setIcon(icon_button);
	}
}

void YJ_User_Block::YJ_set_button_state(bool state)
{
	button_state = state;
}

void YJ_User_Block::YJ_set_username(QString user)
{
	username = user;
	ui.username_label->setText(user);
}
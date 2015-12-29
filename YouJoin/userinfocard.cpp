#include "userinfocard.h"

YJ_User_Info_Card::YJ_User_Info_Card(user_info info,
	QWidget *parent /* = 0 */, bool showAddButton)
	:
	//QWidget(parent),
	user(info),
	isShowAddButton(showAddButton)
{
	ui.setupUi(this);
	yj_init_ui();
	yj_init_connections();
	
}

void YJ_User_Info_Card::yj_init_ui()
{
	//È¥³ý±êÌâÀ¸
	this->setWindowFlags(Qt::FramelessWindowHint);
	//´°¿ÚÍÏ¶¯
	QWidgetResizeHandler *movewin = new QWidgetResizeHandler(this);
	movewin->setMovingEnabled(true);
	//¹Ì¶¨´óÐ¡
	this->setFixedSize(1025, 600);
	//±³¾°Í¸Ã÷
	setAttribute(Qt::WA_TranslucentBackground);

	QIcon icon_close_button;
	icon_close_button.addFile(":/YouJoin/Resources/background-guide-x.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.close_button->setIcon(icon_close_button);
	ui.close_button->setFlat(true);
	ui.close_button->setFocusPolicy(Qt::NoFocus);
	ui.close_button->setIconSize(QSize(14, 14));

	if (isShowAddButton){
		QIcon icon_add_button;
		icon_add_button.addFile(":/YouJoin/Resources/add-friend.png", QSize(), QIcon::Normal, QIcon::Off);
		ui.add_button->setIcon(icon_add_button);
		ui.add_button->setFlat(true);
		ui.add_button->setFocusPolicy(Qt::NoFocus);
		ui.add_button->setIconSize(QSize(27, 26));
	}
	else ui.add_button->setVisible(false);


	ui.username_label->setWordWrap(true);
	ui.username_label->setFont(QFont(QString::fromLocal8Bit("Î¢ÈíÑÅºÚ"), 15));
	ui.username_label->setStyleSheet("color:white;");
	ui.username_label->setText(user.get_username());

	ui.sex_label->setWordWrap(true);
	ui.sex_label->setFont(QFont(QString::fromLocal8Bit("Î¢ÈíÑÅºÚ"), 13));
	ui.sex_label->setStyleSheet("color:white;");
	ui.sex_label->setText(user.get_detail()->get_sex());

	ui.location_label->setWordWrap(true);
	ui.location_label->setFont(QFont(QString::fromLocal8Bit("Î¢ÈíÑÅºÚ"), 13));
	ui.location_label->setStyleSheet("color:white;");
	ui.location_label->setText(user.get_detail()->get_location_city());

	ui.birth_label->setWordWrap(true);
	ui.birth_label->setFont(QFont(QString::fromLocal8Bit("Î¢ÈíÑÅºÚ"), 13));
	ui.birth_label->setStyleSheet("color:white;");
	ui.birth_label->setText(user.get_detail()->get_birthyear());

	ui.hobby_label->setWordWrap(true);
	ui.hobby_label->setFont(QFont(QString::fromLocal8Bit("Î¢ÈíÑÅºÚ"), 13));
	ui.hobby_label->setStyleSheet("color:white;");
	LList<QString> hobbies = user.get_detail()->get_hobbies();
	for (hobbies.moveToStart(); hobbies.currPos() < hobbies.length(); hobbies.next()){
		ui.hobby_label->setText(ui.hobby_label->text() + '\n' + hobbies.getValue());
	}
	
	ui.profession_label->setWordWrap(true);
	ui.profession_label->setFont(QFont(QString::fromLocal8Bit("Î¢ÈíÑÅºÚ"), 13));
	ui.profession_label->setStyleSheet("color:white;");
	ui.profession_label->setText(user.get_detail()->get_work());
}

void YJ_User_Info_Card::yj_init_connections()
{
	connect(ui.close_button, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.add_button, SIGNAL(clicked()), this, SLOT(yj_add_button_clicked()));
}

void YJ_User_Info_Card::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.drawPixmap(0, 0, QPixmap(":/YouJoin/Resources/userinformation-bg.png"));
}

void YJ_User_Info_Card::yj_add_button_clicked()
{
	//if (user.get_user_id() <= 10000000) return;

	emit YJ_add_friend(user.get_user_id());
}


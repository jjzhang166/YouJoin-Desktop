#include "photoblock.h"

YJ_Photo_Block::YJ_Photo_Block(QWidget *parent /* = 0 */)
: QWidget(parent)
{
	ui.setupUi(this);
	yj_init_ui();
	yj_init_connections();

}

YJ_Photo_Block::~YJ_Photo_Block(){}

void YJ_Photo_Block::yj_init_ui()
{
	picButton1 = new QPushButton(this);
	picButton1->setGeometry(QRect(695, 20, 123, 74));
	picButton2 = new QPushButton(this);
	picButton2->setGeometry(QRect(695, 105, 123, 74));
	picButton3 = new QPushButton(this);
	picButton3->setGeometry(QRect(695, 190, 123, 74));

	QIcon icon_1;
	icon_1.addFile(":/YouJoin/Resources/pic1mini.png", QSize(), QIcon::Normal, QIcon::Off);
	picButton1->setIcon(icon_1);
	picButton1->setFlat(true);
	picButton1->setFocusPolicy(Qt::NoFocus);
	picButton1->setIconSize(QSize(123, 74));

	QIcon icon_2;
	icon_2.addFile(":/YouJoin/Resources/pic2mini.png", QSize(), QIcon::Normal, QIcon::Off);
	picButton2->setIcon(icon_2);
	picButton2->setFlat(true);
	picButton2->setFocusPolicy(Qt::NoFocus);
	picButton2->setIconSize(QSize(123, 74));

	QIcon icon_3;
	icon_3.addFile(":/YouJoin/Resources/pic3mini.png", QSize(), QIcon::Normal, QIcon::Off);
	picButton3->setIcon(icon_3);
	picButton3->setFlat(true);
	picButton3->setFocusPolicy(Qt::NoFocus);
	picButton3->setIconSize(QSize(123, 74));

	ui.pic_label->setPixmap(QPixmap(":/YouJoin/Resources/pic1.png"));
}

void YJ_Photo_Block::yj_init_connections()
{
	connect(picButton1, SIGNAL(clicked()), this, SLOT(yj_change_pic1()));
	connect(picButton2, SIGNAL(clicked()), this, SLOT(yj_change_pic2()));
	connect(picButton3, SIGNAL(clicked()), this, SLOT(yj_change_pic3()));
}

void YJ_Photo_Block::yj_change_pic1()
{
	ui.pic_label->setPixmap(QPixmap(":/YouJoin/Resources/pic1.png"));
}

void YJ_Photo_Block::yj_change_pic2()
{
	ui.pic_label->setPixmap(QPixmap(":/YouJoin/Resources/pic2.png"));
}

void YJ_Photo_Block::yj_change_pic3()
{
	ui.pic_label->setPixmap(QPixmap(":/YouJoin/Resources/pic3.png"));
}
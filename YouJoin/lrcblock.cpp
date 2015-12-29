#include "lrcblock.h"

YJ_Lrc_Block::YJ_Lrc_Block(QWidget *parent /* = 0 */)
: QTextEdit(parent)
{

	//this->setWordWrap(true);
	this->setFont(QFont(QString::fromLocal8Bit("Î¢ÈíÑÅºÚ"), 12));
	this->setStyleSheet(
		"color:lightgray;"
		);
	this->setAlignment(Qt::AlignCenter);
	//this->setAttribute(Qt::WA_TranslucentBackground);
	//setAttribute(Qt::WA_TranslucentBackground, true);
	//this->setReadOnly(true);


}

YJ_Lrc_Block::~YJ_Lrc_Block(){}

void YJ_Lrc_Block::paintEvent(QPaintEvent *e)
{
	QPainter p(this);
	p.drawPixmap(0, 0, QPixmap(":/YouJoin/Resources/homepage-background.png"));
}

void YJ_Lrc_Block::YJ_set_text(const QString &text)
{
	content = text;
	this->setText(text);
}

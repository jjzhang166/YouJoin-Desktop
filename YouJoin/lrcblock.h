//ÍøÂç¸è´ÊÄ£¿é

#ifndef LRC_BLOCK_H
#define LRC_BLOCK_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPalette>
#include <QPainter>

class YJ_Lrc_Block : public QTextEdit{
	Q_OBJECT
public:
	YJ_Lrc_Block(QWidget *parent = 0);
	~YJ_Lrc_Block();

	void YJ_set_text(const QString &text);

private:

	void paintEvent(QPaintEvent *e);

	QString content;

};

#endif
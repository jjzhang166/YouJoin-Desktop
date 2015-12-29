//photo“≥√Ê

#ifndef PHOTO_BLOCK_H
#define PHOTO_BLOCK_H

#include <QObject>
#include <QtWidgets>
#include "ui_photoblock.h"

class YJ_Photo_Block : public QWidget{
	
	Q_OBJECT

public:
	YJ_Photo_Block(QWidget *parent = 0);
	~YJ_Photo_Block();


private slots:

	void yj_change_pic1();
	void yj_change_pic2();
	void yj_change_pic3();

private:

	void yj_init_ui();
	void yj_init_connections();

	QPushButton *picButton1;
	QPushButton *picButton2;
	QPushButton *picButton3;

	Ui::photoblock ui;
};


#endif //PHOTO_BLOCK_H
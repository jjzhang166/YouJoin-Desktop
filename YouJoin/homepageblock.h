//主页面
//类名：YJ_Homepage_Block
//功能：显示主页面

#ifndef HOMEPAGE_BLOCK_H
#define HOMEPAGE_BLOCK_H

#include <QWidget>
#include "weatherblock.h"


class YJ_Homepage_Block : public QWidget{

	Q_OBJECT

public :

	YJ_Homepage_Block(QWidget *parent = 0);
	~YJ_Homepage_Block();

private:
	void yj_init_ui();

	YJ_Weather_Block *weather_block;
};

#endif //HOMEPAGE_BLOCK_H
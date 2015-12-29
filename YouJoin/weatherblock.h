//天气模块

#ifndef WEATHER_BLOCK_H
#define WEATHER_BLOCK_H

#include "ui_weatherblock.h"
#include "weatherinfo.h"
#include "network.h"
#include <QWidget>
#include <QPainter>
#include <QIcon>
#include <QString>
#include <QJsonDocument>


class YJ_Weather_Block : public QWidget{
	
	Q_OBJECT
	
public :

	YJ_Weather_Block(QWidget *parent = 0);
	~YJ_Weather_Block();


private:

	void paintEvent(QPaintEvent *event);
	
	//获取天气数据
	void yj_fetch_weather(const QString &city_name) const;

	Ui::weather_block ui;

	YJ_Weather_Info info;
	NetWorker *networker;
	QString city_name;




};



#endif //WEATHER_BLOCK_H
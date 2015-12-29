//////////////////////////////////////////////////////////////////////////
// 文件名：locationpicker.h
// 类名：YJ_Location_Picker
// 类简介：中国的Province-City二级级联选择Combobox
// 作者：ZZQ
//////////////////////////////////////////////////////////////////////////

#ifndef LOCATION_PICKER_H
#define LOCATION_PICKER_H

#include <QtWidgets>
#include <QJsonDocument>
#include <QVariantMap>
#include "ui_locationpicker.h"

class YJ_Location_Picker : public QWidget{
	
	Q_OBJECT

public:

	YJ_Location_Picker(QWidget *parent = 0);
	~YJ_Location_Picker();

	//获取当前选择的地区
	QString YJ_Get_Location();

protected slots:
	
	//初始化信号槽
	void yj_init_connections();
	
	//当省份改变时，刷新城市列表
	void yj_province_changed(int index);
	
	//初始化ui显示
	void yj_init_ui();

private:

	//初始化省份，城市数据
	void yj_init_data();
	

	QVariantMap locationMap;
	QStringList provinceList;
	QStringList provinceNumList;
	QStringList cityList;
	QStringList cityNumList;

	Ui::location_picker ui;

};

#endif //LOCATION_PICKER_H
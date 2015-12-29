//////////////////////////////////////////////////////////////////////////
// �ļ�����locationpicker.h
// ������YJ_Location_Picker
// ���飺�й���Province-City��������ѡ��Combobox
// ���ߣ�ZZQ
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

	//��ȡ��ǰѡ��ĵ���
	QString YJ_Get_Location();

protected slots:
	
	//��ʼ���źŲ�
	void yj_init_connections();
	
	//��ʡ�ݸı�ʱ��ˢ�³����б�
	void yj_province_changed(int index);
	
	//��ʼ��ui��ʾ
	void yj_init_ui();

private:

	//��ʼ��ʡ�ݣ���������
	void yj_init_data();
	

	QVariantMap locationMap;
	QStringList provinceList;
	QStringList provinceNumList;
	QStringList cityList;
	QStringList cityNumList;

	Ui::location_picker ui;

};

#endif //LOCATION_PICKER_H
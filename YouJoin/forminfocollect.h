//用户资料搜集页面

#ifndef FORM_INFO_COLLECT_H
#define FORM_INFO_COLLECT_H

#include <QtWidgets>
#include <QObject>
#include "ui_infocollectform.h"
#include "locationpicker.h"
#include "userinfo.h"
#include "constants.h"

class YJ_InfoCollection_Form : public QWidget{

	Q_OBJECT

public:
	YJ_InfoCollection_Form(QWidget *parent = 0);
	~YJ_InfoCollection_Form();

	//获取当前的选项构成的用户详细信息
	user_detail getDetail();

	//设置用户详细信息
	void setDetail(user_detail detail);

signals:

	//用户资料更新的信号
	void YJ_Detail_Update();

private slots:

	//保存按钮单击槽
	void yj_ok_button_clicked();

private:

	//初始化窗体ui
	void yj_init_ui();

	//初始化信号-槽连接
	void yj_init_connections();

	//初始化信息显示
	void yj_init_show_info();

	Ui::InfoCollectionForm ui;
	YJ_Location_Picker *locationPicker;
	QButtonGroup sexRadioGroup;
	QButtonGroup hobbiesCheckGroup;

	user_detail detail;

};

#endif //FORM_INFO_COLLECT_H
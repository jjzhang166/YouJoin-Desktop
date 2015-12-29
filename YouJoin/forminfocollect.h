//�û������Ѽ�ҳ��

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

	//��ȡ��ǰ��ѡ��ɵ��û���ϸ��Ϣ
	user_detail getDetail();

	//�����û���ϸ��Ϣ
	void setDetail(user_detail detail);

signals:

	//�û����ϸ��µ��ź�
	void YJ_Detail_Update();

private slots:

	//���水ť������
	void yj_ok_button_clicked();

private:

	//��ʼ������ui
	void yj_init_ui();

	//��ʼ���ź�-������
	void yj_init_connections();

	//��ʼ����Ϣ��ʾ
	void yj_init_show_info();

	Ui::InfoCollectionForm ui;
	YJ_Location_Picker *locationPicker;
	QButtonGroup sexRadioGroup;
	QButtonGroup hobbiesCheckGroup;

	user_detail detail;

};

#endif //FORM_INFO_COLLECT_H
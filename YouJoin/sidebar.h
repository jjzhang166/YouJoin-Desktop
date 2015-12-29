//�Զ�����������
//������YJ_Sidebar
//���ܣ��ڴ�������ʾһ�������������һϵ�а�ť
//		���²�ͬ��ťʱ�����л�Ч��

#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QtWidgets/QWidget>
#include "ui_sidebar.h"
#include <QPainter>
#include <QIcon>
#include <QString>
#include "ipushbutton.h"

//��ÿ����ť����Ϣ��װ����
struct Button_Info{
	//��ťָ��
	//QPushButton *name;
	I_PushButton *name;

	//��ť��״̬��true��ʾ���£�false��ʾδ����
	bool state;
	
	//��ť����ʱ��ͼ��
	QString pushed_icon;
	
	//��ťδ����ʱ��ͼ��
	QString unpushed_icon;
};

//����ť���
enum BUTTON_FLAG{
	HOMEPAGE, FRIEND, RECOMMEND, PHOTO, MUSIC, VIDEO, MORE
};

class YJ_Sidebar : public QWidget
{
	Q_OBJECT

public :
	YJ_Sidebar(QWidget *parent = 0);
	~YJ_Sidebar();

signals:
	//һϵ�а�ť�ĵ����ź�
	void yj_homepage_button_clicked(int);
	void yj_friend_button_clicked(int);
	void yj_recommend_button_clicked(int);
	void yj_photo_button_clicked(int);
	void yj_music_button_clicked(int);
	void yj_video_button_clicked(int);
	void yj_more_button_clicked(int);


private slots:
	//һϵ�а�ť�ĵ����¼�
	void yj_homepage_button_click();
	void yj_friend_button_click();
	void yj_recommend_button_click();
	void yj_photo_button_click();
	void yj_music_button_click();
	void yj_video_button_click();
	void yj_more_button_click();

private:
	//���Ʋ�������
	void paintEvent(QPaintEvent *event);

	//��ʼ������UI
	void yj_init_ui();

	//��ʼ�������ź�-������
	void yj_init_connections();

	//��ʼ������ť��Ϣ��״̬��ͼ��
	void yj_init_button_info();

	//��ȡ��ǰ���µİ�ť���
	int yj_get_pushed_button();

	//���ð�ťΪ����״̬
	void yj_set_pushed_button(int button_flag);

	//���ð�ťΪδ����״̬
	void yj_set_unpushed_button(int button_flag);

	
	Ui::Sidebar ui;

	//��ť��
	Button_Info button_group[7];


};



#endif //SIDEBAR_H
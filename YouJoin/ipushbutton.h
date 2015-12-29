//���ư�ť

#ifndef I_PUSH_BUTTON_H
#define I_PUSH_BUTTON_H

#include <QtGui> 
#include <QPushButton>

class I_PushButton : public QPushButton
{
	Q_OBJECT
private:
	QIcon normalIcon;
	QIcon focusIcon;
	QIcon pressedIcon;
protected:

	//���ء����롱�͡��뿪���¼�������ʱ�л�Ϊ��һ��ͼ�꣬�뿪ʱ��ԭ 
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);

	//������갴�º��ɿ��¼� ���л�ͼ��
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
public:
	I_PushButton(QWidget *parent = 0);
	~I_PushButton();

	//����ͼ��
	//��ָֻ��һ��ͼ�꣬��Ĭ�ϡ����롱�����£��ɿ���Ϊ��ͼ��
	void Set_Button_Icons(
		const QIcon &normal, 
		const QIcon &focus = QIcon(), 
		const QIcon &pressed = QIcon()
		);
};

#endif //I_PUSH_BUTTON_H
#include "ipushbutton.h"

I_PushButton::I_PushButton(QWidget *parent)
: QPushButton(parent)
{
	//setDown(false);  

	//设置图标无焦点
	setFocusPolicy(Qt::NoFocus);
	setAttribute(Qt::WA_TranslucentBackground);
	//QWidgetResizeHandler *movewin = new QWidgetResizeHandler(this);
	//movewin->setMovingEnabled(true);
}

I_PushButton::~I_PushButton()
{

}

void I_PushButton::enterEvent(QEvent *event)
{
 	if (isEnabled() && !normalIcon.isNull())
 		setIcon(normalIcon);
}

void I_PushButton::leaveEvent(QEvent *event)
{
	if (isEnabled())
		setIcon(normalIcon);
}


void I_PushButton::mousePressEvent(QMouseEvent *event)
{
	if (isEnabled() && !normalIcon.isNull())
		setIcon(normalIcon);
	QPushButton::mousePressEvent(event);
}

void I_PushButton::mouseReleaseEvent(QMouseEvent *event)
{
	if (isEnabled() && !normalIcon.isNull())
		setIcon(normalIcon);
	QPushButton::mouseReleaseEvent(event);
}

void I_PushButton::Set_Button_Icons(
	const QIcon &normal, 
	const QIcon &focus, 
	const QIcon &pressed
	)
{
	normalIcon = normal;
	focusIcon = normal;
	pressedIcon = normal;
	setIcon(normalIcon);
}

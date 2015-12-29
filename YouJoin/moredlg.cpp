#include "moredlg.h"

YJ_More_Dlg::YJ_More_Dlg(QString bg, QWidget *parent /* = 0 */)
: QDialog(parent),
background(bg)
{
	ui.setupUi(this);
	QIcon icon_close_button;
	icon_close_button.addFile(":/YouJoin/Resources/background-guide-x.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.close_button->setIcon(icon_close_button);
	ui.close_button->setFlat(true);
	ui.close_button->setFocusPolicy(Qt::NoFocus);

	//ȥ��������
	this->setWindowFlags(Qt::FramelessWindowHint);
	//�̶���С
	this->setFixedSize(656, 464);
	//����͸��
	setAttribute(Qt::WA_TranslucentBackground);
	//���ñ�����Ϊģʽ���ڣ����������޷���������棩
	this->setModal(true);
	//�����϶�
	QWidgetResizeHandler *movewin = new QWidgetResizeHandler(this);
	movewin->setMovingEnabled(true);

	connect(ui.close_button, SIGNAL(clicked()), this, SLOT(close()));
}

YJ_More_Dlg::~YJ_More_Dlg(){}

void YJ_More_Dlg::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.drawPixmap(0, 0, QPixmap(background));
}
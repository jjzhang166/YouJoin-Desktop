#include "moreblock.h"

YJ_More_Block::YJ_More_Block(QWidget *parent /* = 0 */)
:QWidget(parent)
{
	ui.setupUi(this);
	yj_init_ui();
	yj_init_connections();
}

void YJ_More_Block::yj_clear_dlg()
{
	if (moredlg != NULL) {
		delete moredlg;
		moredlg = NULL;
	}
}

void YJ_More_Block::yj_agreement_button_clicked()
{
	yj_clear_dlg();
	moredlg = new YJ_More_Dlg(":/YouJoin/Resources/about-dlg.png");
	moredlg->show();
}

void YJ_More_Block::yj_connect_button_clicked()
{
	yj_clear_dlg();
	moredlg = new YJ_More_Dlg(":/YouJoin/Resources/connect-dlg.png");
	moredlg->show();
}

void YJ_More_Block::yj_update_button_clicked()
{
	yj_clear_dlg();
	moredlg = new YJ_More_Dlg(":/YouJoin/Resources/update-dlg.png");
	moredlg->show();
}

void YJ_More_Block::yj_setup_button_clicked()
{
// 	yj_clear_dlg();
// 	moredlg = new YJ_More_Dlg(":/YouJoin/Resources/about-dlg.png");
// 	moredlg->show();
	emit YJ_show_self();
}

void YJ_More_Block::yj_quit_button_clicked()
{
	emit YJ_quit();
}


void YJ_More_Block::yj_init_connections()
{
	connect(ui.agreement_button, SIGNAL(clicked()), this, SLOT(yj_agreement_button_clicked()));
	connect(ui.connect_Button, SIGNAL(clicked()), this, SLOT(yj_connect_button_clicked()));
	connect(ui.setup_button, SIGNAL(clicked()), this, SLOT(yj_setup_button_clicked()));
	connect(ui.update_button, SIGNAL(clicked()), this, SLOT(yj_update_button_clicked()));
	connect(ui.quit_button, SIGNAL(clicked()), this, SLOT(yj_quit_button_clicked()));
}

void YJ_More_Block::yj_init_ui()
{
	QIcon icon_agreement_button;
	icon_agreement_button.addFile(":/YouJoin/Resources/button-agreement.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.agreement_button->setIcon(icon_agreement_button);
	ui.agreement_button->setFlat(true);
	ui.agreement_button->setFocusPolicy(Qt::NoFocus);
	ui.agreement_button->setIconSize(QSize(191, 31));

	QIcon icon_connect_Button;
	icon_connect_Button.addFile(":/YouJoin/Resources/button-contactus.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.connect_Button->setIcon(icon_connect_Button);
	ui.connect_Button->setFlat(true);
	ui.connect_Button->setFocusPolicy(Qt::NoFocus);
	ui.connect_Button->setIconSize(QSize(191, 31));

	QIcon icon_setup_button;
	icon_setup_button.addFile(":/YouJoin/Resources/button-setup.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.setup_button->setIcon(icon_setup_button);
	ui.setup_button->setFlat(true);
	ui.setup_button->setFocusPolicy(Qt::NoFocus);
	ui.setup_button->setIconSize(QSize(191, 31));

	QIcon icon_update_button;
	icon_update_button.addFile(":/YouJoin/Resources/button-update.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.update_button->setIcon(icon_update_button);
	ui.update_button->setFlat(true);
	ui.update_button->setFocusPolicy(Qt::NoFocus);
	ui.update_button->setIconSize(QSize(191, 31));

	QIcon icon_quit_button;
	icon_quit_button.addFile(":/YouJoin/Resources/button-quit.png", QSize(), QIcon::Normal, QIcon::Off);
	ui.quit_button->setIcon(icon_quit_button);
	ui.quit_button->setFlat(true);
	ui.quit_button->setFocusPolicy(Qt::NoFocus);
	ui.quit_button->setIconSize(QSize(77, 30));
}


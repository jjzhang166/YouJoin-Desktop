//more“≥√Ê

#ifndef MORE_BLOCK_H
#define MORE_BLOCK_H

#include <QObject>
#include <QtWidgets>
#include "ui_moreblock.h"
#include "moredlg.h"

class YJ_More_Block : public QWidget{

	Q_OBJECT

public:
	YJ_More_Block(QWidget *parent = 0);
	~YJ_More_Block(){}

signals:
	void YJ_show_self();
	void YJ_quit();

private slots:

	void yj_connect_button_clicked();
	void yj_setup_button_clicked();
	void yj_update_button_clicked();
	void yj_agreement_button_clicked();
	void yj_quit_button_clicked();

private:

	void yj_init_ui();
	void yj_init_connections();
	void yj_clear_dlg();

	Ui::more_block ui;

	YJ_More_Dlg *moredlg = NULL;

};

#endif //MORE_BLOCK_H
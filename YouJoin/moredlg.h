//更多对话框

#ifndef	MORE_DLG_H
#define MORE_DLG_H

#include <QtWidgets>
#include <QObject>
#include <QDialog>
#include <qwidgetresizehandler_p.h>
#include "ui_moredlg.h"

class YJ_More_Dlg : public QDialog
{
	Q_OBJECT
public:
	YJ_More_Dlg(QString bg, QWidget *parent = 0);
	~YJ_More_Dlg();


private:
	//绘制背景图片
	void paintEvent(QPaintEvent *event);

	QString background;

	Ui::more_dlg ui;
};

#endif //MORE_DLG_H

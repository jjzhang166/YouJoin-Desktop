//È¥³ýqtablewidgetitemµÄÐé¿ò

#ifndef NOFOCUSDELEGATE_H
#define NOFOCUSDELEGATE_H
#include <QStyledItemDelegate>

class QPainter;
class QStyleOptionViewItem;
class QModelIndex;
class QStyledItemDelegate;

class NoFocusDelegate : public QStyledItemDelegate
{
protected:
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
};


#endif //NOFOCUSDELEGATE_H
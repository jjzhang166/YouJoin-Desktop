#include "nofocusdelegate.h"

#include <QPainter>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include <QModelIndex>

void NoFocusDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const
{
	QStyleOptionViewItem itemOption(option);
	if (itemOption.state & QStyle::State_HasFocus)
		itemOption.state = itemOption.state ^ QStyle::State_HasFocus;
	QStyledItemDelegate::paint(painter, itemOption, index);
}
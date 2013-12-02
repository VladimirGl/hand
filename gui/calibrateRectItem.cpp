#include "calibrateRectItem.h"

#include "guiConsts.h"

#include "../map.h"

#include <QBrush>
#include <QPen>

#include <QDebug>

CalibrateRectItem::CalibrateRectItem() :
	mMinLine(new QGraphicsLineItem(0, 0, CalibrateRect::rectW, 0, this)),
	mMaxLine(new QGraphicsLineItem(0, 0, CalibrateRect::rectW, 0, this)),
	mCurrValueRect(new QGraphicsRectItem(0, 0, CalibrateRect::rectW, 0, this))
{
	this->setRect(0, 0, CalibrateRect::rectW, CalibrateRect::rectH);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(QColor("#009900"));

	setBoard();
	setLineBrush();
	setRectBrush();

	mMinLine->setZValue(50);
	mMaxLine->setZValue(50);

	mCurrValueRect->setZValue(25);
}

void CalibrateRectItem::setCalibrateingData(const int &min, const int &max, const int &value)
{
	mMinLine->setPos(0
			, CalibrateRect::rectH
					 - Map::map(min
							, CalibrateRect::min
							, CalibrateRect::max
							, 0
							, CalibrateRect::rectH)
			);

	mMaxLine->setPos(0
			, CalibrateRect::rectH
					 - Map::map(max
							, CalibrateRect::min
							, CalibrateRect::max
							, 0
							, CalibrateRect::rectH)
			);

	int y = Map::map(value
			, CalibrateRect::min
			, CalibrateRect::max
			, 0
			, CalibrateRect::rectH);

	mCurrValueRect->setRect(0
			, CalibrateRect::rectH - y
			, CalibrateRect::rectW
			, y
			);
}

void CalibrateRectItem::setBoard()
{
	QGraphicsRectItem *item = new QGraphicsRectItem(0, 0, CalibrateRect::rectW, CalibrateRect::rectH);

	QPen pen;
	pen.setWidth(2);

	item->setPen(pen);
	item->setZValue(100);
}

void CalibrateRectItem::setLineBrush()
{
	QPen pen;
	pen.setColor(QColor("#FF3300"));

	mMinLine->setPen(pen);
	mMaxLine->setPen(pen);
}

void CalibrateRectItem::setRectBrush()
{
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(QColor("#009900"));

	mCurrValueRect->setBrush(brush);
}

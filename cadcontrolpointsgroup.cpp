#include "cadcontrolpointsgroup.h"

CadControlPointsGroup::CadControlPointsGroup()
{
//    QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable, true);
//    QGraphicsItem::setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void CadControlPointsGroup::setPoints(QPolygonF *newPoints)
{
    points = newPoints;
    QGraphicsRectItem * rectItem;

    for(int i = 0; i<points->size();i++)
    {
        QPointF p = points->value(i);
        QPointF p1 = p - QPointF(3,3);
        QPointF p2 = p + QPointF(3,3);
        QRectF r = QRectF(p1,p2);

        rectItem = new QGraphicsRectItem(r,this);
        rectItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        rectItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        addToGroup(rectItem);
    }
}

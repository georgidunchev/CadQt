#ifndef CADCONTROLPOINTSITEM_H
#define CADCONTROLPOINTSITEM_H

#include <QGraphicsItemGroup>
#include "cadcontrolpointrectitem.h"

class CadControlPointsItem : public QGraphicsItemGroup
{
public:
    CadControlPointsItem(QGraphicsItem * parent = 0);
    void setPoints(const QPolygonF & newPoints, const QPointF & newOriginPoint);
    void updatePoints(const QPolygonF & newPoints, const QPointF & newOriginPoint);
    void setVisible(bool visible);
    bool controlPointSelected();
private:
    QPolygonF points;
    QList<CadControlPointRectItem*> controlPointItems;
    CadControlPointRectItem * originPoint;
};

#endif // CADCONTROLPOINTSITEM_H

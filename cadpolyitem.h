#ifndef CADPOLYITEM_H
#define CADPOLYITEM_H

#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include "caditem.h"

class CadPolyItem :  public CadItem, public QGraphicsPolygonItem
{
public:
    CadPolyItem(CadType cadType);

    enum { Type = UserType+4};
    int type() const
        { return Type; }

    bool isFinished();
    void setShape(bool transform = true);

    void addPoint(QPointF point);
    void addTempPoint(QPointF point);

    QGraphicsItem * getItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


#endif // CADPOLYITEM_H



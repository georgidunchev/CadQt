#ifndef CADRECTITEM_H
#define CADRECTITEM_H

#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include "caditem.h"

class CadRectItem : public CadItem, public QGraphicsPolygonItem
{
public:
    CadRectItem(CadType cadType);

    enum { Type = UserType+3};
    int type() const
        { return Type; }

    bool isFinished();
    void addPoint(QPointF point);
    void addTempPoint(QPointF point);

    QGraphicsItem * getItem();
    void translate(QPointF modifier);

    void setShape(bool transform = true);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void updatePointsPolygon(int id, QPointF newPoint);

private:
    QPointF p1,p2;
    int nOfPoints;
    QPolygonF rectToPoly(QPointF p1, QPointF p2);
};

#endif // CADRECTITEM_H

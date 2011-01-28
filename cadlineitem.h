#ifndef CADLINEITEM_H
#define CADLINEITEM_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include "caditem.h"


class CadLineItem : virtual public CadItem, public QGraphicsLineItem
{
public:
    CadLineItem(CadType cadType);

    enum { Type = UserType+1};
    int type() const
        { return Type; }

    bool isFinished();
    void addPoint(QPointF point);
    void addTempPoint(QPointF point);
    QGraphicsItem * getItem();
    void translate(QPointF modifier);
    void setShape(bool transform = true);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    QPointF p1,p2;
    int nOfPoints;
};

#endif // CADLINEITEM_H

#ifndef CADCURVEITEM_H
#define CADCURVEITEM_H

#include <QGraphicsPathItem>
#include "caditem.h"

class CadCurveItem : public CadItem, public QGraphicsPathItem
{
public:
    CadCurveItem(CadType cadType);

    enum { Type = UserType+2};
    int type() const
        { return Type; }

    bool isFinished();
    void addPoint(QPointF point);
    void addTempPoint(QPointF point);

    QGraphicsItem * getItem();

    void setShape(bool transform = true);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int nOfPoints;
    QVector<qreal> calcB(qreal t) const;
};

#endif // CADCURVEITEM_H

#ifndef CADCONTROLPOINTRECTITEM_H
#define CADCONTROLPOINTRECTITEM_H

#include <QGraphicsRectItem>
#include "cadcontrolpointrectitem.h"
//#include "caditem.h"
//#include "mainwindow.h"
class CadItem;

class CadControlPointRectItem : public QGraphicsRectItem
{
//        Q_OBJECT
public:
    CadControlPointRectItem(int id, const QPointF & point, CadItem * parentCI,  QGraphicsItem * parent = 0, bool edgePoint = true);

    enum { Type = UserType+5};
    int type() const
        { return Type; }

    void setPoint(const QPointF & point);

private:
    QRectF calcRect();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    CadItem * parentCadItem;
    int controlPointId;
    bool isEdgePoint;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CADCONTROLPOINTRECTITEM_H

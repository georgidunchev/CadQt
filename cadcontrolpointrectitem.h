#ifndef CADCONTROLPOINTRECTITEM_H
#define CADCONTROLPOINTRECTITEM_H

#include <QGraphicsRectItem>
#include "cadcontrolpointrectitem.h"
//#include "caditem.h"
//#include "mainwindow.h"
class CadItem;

class CadControlPointRectItem : public QGraphicsRectItem
{
public:
    CadControlPointRectItem(int id, const QPointF & point, CadItem * parentCadItem,  QGraphicsItem * parent = 0, bool edgePoint = true);

    enum { Type = UserType+5};
    int type() const
        { return Type; }

    void setPoint(const QPointF & point);

private:
    QRectF calcRect();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    CadItem * parentItem;
    int controlPointId;
    bool isEdgePoint;
};

#endif // CADCONTROLPOINTRECTITEM_H

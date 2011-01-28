#ifndef CADCONTROLPOINTRECTITEM_H
#define CADCONTROLPOINTRECTITEM_H

#include <QGraphicsRectItem>
#include "cadcontrolpointrectitem.h"
//#include "caditem.h"
//#include "mainwindow.h"

class CadControlPointRectItem : public QGraphicsRectItem
{
public:
    CadControlPointRectItem(int id, const QPointF & point, QGraphicsItem * parent = 0);

    enum { Type = UserType+5};
    int type() const
        { return Type; }

    void setPoint(const QPointF & point);
private:
    int controlPointId;
    QRectF calcRect();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    MainWindow * mw;
};

#endif // CADCONTROLPOINTRECTITEM_H

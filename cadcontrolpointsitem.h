#ifndef CADCONTROLPOINTSITEM_H
#define CADCONTROLPOINTSITEM_H

#include <QGraphicsItemGroup>
#include "cadcontrolpointrectitem.h"
//#include "mainwindow.h"

class CadControlPointsItem : public QGraphicsItemGroup
{
public:
    CadControlPointsItem();
    void setPoints(const QPolygonF & newPoints);
    void updatePoints(const QPolygonF & newPoints);
    void setVisible(bool visible);
    bool controlPointSelected();
private:
//    void addControlPoint(QPointF p);
    QPolygonF points;
    QList<CadControlPointRectItem*> controlPointItems;
//    MainWindow * mw;
};

#endif // CADCONTROLPOINTSITEM_H

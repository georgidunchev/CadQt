#include "cadcontrolpointrectitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDebug>
#include "caditem.h"
//#include "mainwindow.h"

CadControlPointRectItem::CadControlPointRectItem(int id, const QPointF &point, CadItem *parentCadItem, QGraphicsItem *parent, bool edgePoint)
    : QGraphicsRectItem(parent)
{
    controlPointId = id;
    setPoint(point);
    parentItem = parentCadItem;
    isEdgePoint=edgePoint;

    QColor color;
    if(edgePoint)
        color = Qt::gray;
    else
        color = Qt::blue;
    setBrush(QBrush(color));
    setPen(QPen(color));

    QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable, true);
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void CadControlPointRectItem::setPoint(const QPointF &point)
{
    setPos(point);
    setRect(calcRect());
}

QRectF CadControlPointRectItem::calcRect()
{
    return QRectF(QPointF(-3,-3),QPointF(3,3));
}

void CadControlPointRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isEdgePoint)
        parentItem->updatePointsPolygon(controlPointId, pos());
    else
        parentItem->updateOriginPoint(pos());
    QGraphicsRectItem::mouseMoveEvent(event);
}

void CadControlPointRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(isEdgePoint)
        parentItem->updatePointsPolygon(controlPointId, pos());
    else
        parentItem->updateOriginPoint(pos());
    QGraphicsRectItem::mouseReleaseEvent(event);
}

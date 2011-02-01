#include "cadcontrolpointrectitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QPainter>
#include "caditem.h"
#include "cadscene.h"
//#include "mainwindow.h"

CadControlPointRectItem::CadControlPointRectItem(int id, const QPointF &point, CadItem *parentCI, QGraphicsItem *parent, bool edgePoint)
    : QGraphicsRectItem(parent)
{
    controlPointId = id;
    setPoint(point);
    parentCadItem = parentCI;
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

void CadControlPointRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    parentItem()->setSelected(true);
    parentItem()->QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable, false);
    QGraphicsRectItem::mousePressEvent(event);
}

void CadControlPointRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    parentItem()->setSelected(true);

    if(isEdgePoint)
        parentCadItem->updatePointsPolygon(controlPointId, pos());
    else
        parentCadItem->updateOriginPoint(pos());
    QGraphicsRectItem::mouseMoveEvent(event);
}

void CadControlPointRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(isEdgePoint)
        parentCadItem->updatePointsPolygon(controlPointId, pos());
    else
    {
        parentCadItem->updateOriginPoint(pos());
    }
    QGraphicsRectItem::mouseReleaseEvent(event);

    setSelected(false);

    parentItem()->setSelected(true);
    parentItem()->QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable, true);
}

void CadControlPointRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QGraphicsRectItem::paint(painter,option,widget);
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawRect(rect());
}

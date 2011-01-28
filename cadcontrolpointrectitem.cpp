#include "cadcontrolpointrectitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDebug>
#include "caditem.h"
#include "mainwindow.h"

CadControlPointRectItem::CadControlPointRectItem(int id, const QPointF &point, QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    controlPointId = id;
    setPoint(point);

    QColor color = Qt::gray;
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
    QPointF p1 = QPointF(-3,-3);
    QPointF p2 = QPointF(3,3);
    return QRectF(p1,p2);
}

void CadControlPointRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    MainWindow * mw =  (MainWindow * ) scene()->parent();
    CadItem * ci = mw->castQGraphicsItemToCadItem(parentItem());
    QPointF newpoint = pos();
    ci->updatePointsPolygon(controlPointId, newpoint);
    QGraphicsRectItem::mouseMoveEvent(event);
}
void CadControlPointRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    MainWindow * mw =  (MainWindow * ) scene()->parent();
    CadItem * ci = mw->castQGraphicsItemToCadItem(parentItem());
    ci->updatePointsPolygon(controlPointId,pos());
    QGraphicsRectItem::mouseReleaseEvent(event);
}

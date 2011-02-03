#include "cadcontrolpointrectitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QPainter>
#include <qmath.h>
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


    if(((CadScene) scene()).getMode()!=CadScene::None)
    {
        tmpPos = scenePos();
    }


    QGraphicsRectItem::mousePressEvent(event);
}

void CadControlPointRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    parentItem()->setSelected(true);
    if(isEdgePoint)
    {
        QPointF originPoint = parentCadItem->getOriginPoint();

        switch (((CadScene *) scene())->getTransMode())
        {
        case (CadScene::Translate):
            {
                factor = QPointF((scenePos().x()-tmpPos.x())
                                 ,(scenePos().y()-tmpPos.y()));
                parentCadItem->translate(factor,true);
            }
            break;
        case (CadScene::Rotate):
            {
                QPointF a = (tmpPos - originPoint);
                QPointF b = (scenePos() - originPoint);
                rotAngle = atan2(a.x(),a.y())-atan2(b.x(),b.y());
                parentCadItem->rotate(rotAngle,true);
            }
            break;
        case (CadScene::Scale):
            {
//                qDebug()<<(scenePos().x()-originPoint.x())<<(scenePos().y()-originPoint.y());
                factor = QPointF((scenePos().x()-originPoint.x())/(tmpPos.x()-originPoint.x())
                                 ,(scenePos().y()-originPoint.y())/(tmpPos.y()-originPoint.y()));

                if(((scenePos().x()-originPoint.x())==0))//<0.1)&&((scenePos().x()-originPoint.x())>-0.1))
                    factor.setX(0.1);

                if((((scenePos().y()-originPoint.y())==0)))//<0.1)) || ((scenePos().y()-originPoint.y())>-0.1))
                    factor.setY(0.1);

                parentCadItem->scale(factor,true);
            }
            break;
        default:
            {
                parentCadItem->updatePointsPolygon(controlPointId, pos());
            }
            break;
        }

    }
    else
        parentCadItem->updateOriginPoint(pos());



    QGraphicsRectItem::mouseMoveEvent(event);
}

void CadControlPointRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(isEdgePoint)
    {
        switch (((CadScene *) scene())->getTransMode())
        {
        case (CadScene::Translate):
            {
                parentCadItem->translate(factor);
            }
            break;
        case (CadScene::Rotate):
            {
                parentCadItem->rotate(rotAngle);
            }
            break;
        case (CadScene::Scale):
            {
                parentCadItem->scale(factor);
            }
            break;
        default:
            {
                parentCadItem->updatePointsPolygon(controlPointId, pos());
            }
            break;
        }
    }
    else
    {
        parentCadItem->updateOriginPoint(pos());
    }
    QGraphicsRectItem::mouseReleaseEvent(event);

    setSelected(false);

    parentItem()->setSelected(true);
//    parentItem()->QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable, true);
}

void CadControlPointRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QGraphicsRectItem::paint(painter,option,widget);
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawRect(rect());
}

uint CadControlPointRectItem::calcLineLength(const QPointF &A, const QPointF &B)
{
    int x = A.x()-B.x();
    int y = A.y()-B.y();
    return sqrt(x*x+y*y);
}

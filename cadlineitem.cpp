#include "cadlineitem.h"
#include "QPen"
#include "cadscene.h"
#include <QDebug>

CadLineItem::CadLineItem(CadType cadType)
    : CadItem(cadType)
{
    nOfPoints=0;
//    QColor color = Qt::black;
//    this->setPen(QPen(color, 2));
//    this->pen().setWidth()=2;
    QColor color = Qt::black;
    setPen(QPen(color, 2));
//    this-

    QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable, true);
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    boundingCircle = new CadBoundingCircle(this);
    boundingCircle->setVisible(false);

    controlPointsGroup = new CadControlPointsItem();
    controlPointsGroup->setVisible(false);
    controlPointsGroup->setParentItem(this);
}

bool CadLineItem::isFinished()
{
    if(nOfPoints==2)
    {
        setConstructed(true);
        setControlPointsItem();
        //        controlPointsGroup->setPoints(getPointsPolygon());
        return true;
    }
    else
        return false;
}

void CadLineItem::addPoint(QPointF point)
{
    this->setSelected(true);
    if(nOfPoints==0)
    {
        pointPolygon<<point;
        pointPolygon<<point;
        nOfPoints=1;
    }
    else if(nOfPoints==1)
    {
        pointPolygon[1]=point;
        boundingCircle->setPoints(getPointsPolygon());
        nOfPoints=2;
    }
    setShape();
}
void CadLineItem::addTempPoint(QPointF point)
{
    if(nOfPoints==1)
    {
        pointPolygon[1]=point;
    }
    setShape();
}
QGraphicsItem *CadLineItem::getItem()
{
    return this;
}

void CadLineItem::translate(QPointF modifier)
{
    QTransform transform;
    transform.translate(modifier.rx(), modifier.ry());
    QGraphicsItem::setTransform(transform,true);
}

void CadLineItem::setShape(bool transform)
{
    if(transform) transformPoints();
    setLine(QLineF(points[0],points[1]));
    CadItem::setShape();
}

void CadLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(((CadScene *) scene())->isBoundingCircleOn())
    {
        if( !isConstructed() || isSelected() )
            boundingCircle->setVisible(true);
        else
            boundingCircle->setVisible(false);
    }
    else
        boundingCircle->setVisible(false);

    if( isSelected()
        || controlPointsGroup->controlPointSelected() )
        controlPointsGroup->setVisible(((CadScene *) scene())->isControlPointsOn());
    else
        controlPointsGroup->setVisible(false);
//    qDebug()<<"pos"<<pos()<<"scene"<<scenePos();
    QGraphicsLineItem::paint(painter,option,widget);
}


#include "cadlineitem.h"
#include "QPen"
#include "cadscene.h"
#include <QDebug>

CadLineItem::CadLineItem(CadType cadType)
    : CadItem(cadType)
{
    nOfPoints=0;
    QColor color = Qt::black;
    setPen(QPen(color, 2));

//    QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable, true);
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsSelectable, true);
    boundingCircle = new CadBoundingCircle(this);
    boundingCircle->setVisible(false);

    controlPointsGroup = new CadControlPointsItem(this);
    controlPointsGroup->setVisible(false);
    controlPointsGroup->setParentItem(this);
}

bool CadLineItem::isFinished()
{
    if(nOfPoints==2)
    {
        setConstructed(true);
        setControlPointsItem();
        return true;
    }
    else
        return false;
}

void CadLineItem::addPoint(QPointF point)
{
    setSelected(true);
    if(nOfPoints==0)
    {
        pointPolygon<<point;
        pointPolygon<<point;
        nOfPoints=1;
    }
    else if(nOfPoints==1)
    {
        pointPolygon[1]=point;
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
    QGraphicsLineItem::paint(painter,option,widget);
}


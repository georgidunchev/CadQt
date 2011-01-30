#include "cadpolyitem.h"
#include "qtransform.h"
#include "cadscene.h"

CadPolyItem::CadPolyItem(CadType cadType) : CadItem(cadType)
{
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable, true);
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsSelectable, true);
//    QGraphicsItem::setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    QColor color = Qt::black;
    setPen(QPen(color, 2));

    boundingCircle = new CadBoundingCircle(this);
    boundingCircle->setVisible(false);

    controlPointsGroup = new CadControlPointsItem();
    controlPointsGroup->setVisible(false);
    controlPointsGroup->setParentItem(this);
}

bool CadPolyItem::isFinished()
{
    if(nOfPoints>2)
    {
        setConstructed(true);
        setControlPointsItem();
//        controlPointsGroup->setPoints(getPointsPolygon());
        return true;
    }
    else
        return false;
}


void CadPolyItem::addPoint(QPointF point)
{
    setSelected(true);
    if(nOfPoints==0)
    {
        pointPolygon<<point;
    }
    else
    {
        pointPolygon<<point;
        setPolygon(pointPolygon);
    }
    nOfPoints++;
    setShape();
    boundingCircle->addPoint(point);
}

void CadPolyItem::addTempPoint(QPointF point)
{
    if(nOfPoints==1)
    {
        pointPolygon<<point;
        setPolygon(pointPolygon);
        pointPolygon.pop_back();
    }
    if(nOfPoints>1)
    {
        pointPolygon<<point;
        setPolygon(pointPolygon);
        pointPolygon.pop_back();
    }
}
QGraphicsItem * CadPolyItem::getItem()
{
    return this;
}

void CadPolyItem::translate(QPointF modifier)
{
    QTransform transform;
    transform.translate(modifier.rx(), modifier.ry());
    QGraphicsItem::setTransform(transform,true);
}

void CadPolyItem::setShape(bool transform)
{
    if(transform) transformPoints();
    setPolygon(points);
    CadItem::setShape();
}

void CadPolyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    QGraphicsPolygonItem::paint(painter,option,widget);
}

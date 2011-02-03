#include "cadrectitem.h"
#include "qtransform.h"
#include "cadscene.h"
#include "qdebug.h"

CadRectItem::CadRectItem(CadType cadType)
    : CadItem(cadType)
{
    nOfPoints=0;
//    QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable, true);
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsSelectable, true);
    QColor color = Qt::black;
    setPen(QPen(color, 2));

    boundingCircle = new CadBoundingCircle(this);
    boundingCircle->setVisible(false);

    controlPointsGroup = new CadControlPointsItem();
    controlPointsGroup->setVisible(false);
    controlPointsGroup->setParentItem(this);
}

bool CadRectItem::isFinished()
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

void CadRectItem::addPoint(QPointF point)
{
    this->setSelected(true);
    if(nOfPoints==0)
    {
        pointPolygon<<point;
        nOfPoints=1;
    }
    else if(nOfPoints==1)
    {
        QPointF first = pointPolygon.first();
        pointPolygon.clear();
        pointPolygon = rectToPoly(first, point);
        nOfPoints=2;
    }
    setShape();
}
void CadRectItem::addTempPoint(QPointF point)
{
    if(nOfPoints==1)
    {
        QPointF first = pointPolygon.first();
        pointPolygon.clear();
        pointPolygon = rectToPoly(first, point);
    }
    setShape();
}

QPolygonF CadRectItem::rectToPoly(QPointF p1, QPointF p2)
{
    QPolygonF polygon;
    polygon<<p1<<QPointF(p1.x(),p2.y())<<p2<<QPointF(p2.x(),p1.y());
    return polygon;
}

void CadRectItem::updatePointsPolygon(int id, QPointF newPoint)
{
    CadItem::updatePointsPolygon(id, newPoint);

    QPointF pointInOriginalSpace, tmp;
    switch (id)
    {
    case 0:
        {
            pointInOriginalSpace = pointPolygon[0];
            tmp = pointPolygon.at(1);
            tmp.setX(pointInOriginalSpace.x());
            pointPolygon[1] = tmp;
            tmp = pointPolygon.at(3);
            tmp.setY(pointInOriginalSpace.y());
            pointPolygon[3] = tmp;
        }
        break;
    case 1:
        {
            pointInOriginalSpace = pointPolygon[1];
            tmp = pointPolygon.at(0);
            tmp.setX(pointInOriginalSpace.x());
            pointPolygon[0] = tmp;
            tmp = pointPolygon.at(2);
            tmp.setY(pointInOriginalSpace.y());
            pointPolygon[2] = tmp;
        }
        break;
    case 2:
        {
            pointInOriginalSpace = pointPolygon[2];
            tmp = pointPolygon.at(3);
            tmp.setX(pointInOriginalSpace.x());
            pointPolygon[3] = tmp;
            tmp = pointPolygon.at(1);
            tmp.setY(pointInOriginalSpace.y());
            pointPolygon[1] = tmp;
        }
        break;
    case 3:
        {
            pointInOriginalSpace = pointPolygon[3];
            tmp = pointPolygon.at(2);
            tmp.setX(pointInOriginalSpace.x());
            pointPolygon[2] = tmp;
            tmp = pointPolygon.at(0);
            tmp.setY(pointInOriginalSpace.y());
            pointPolygon[0] = tmp;
        }
        break;
    }
    setShape();
    controlPointsGroup->updatePoints(points, originPoint);

}

QGraphicsItem * CadRectItem::getItem()
{
    return this;
}

void CadRectItem::setShape(bool transform)
{
    if(transform) transformPoints();
    setPolygon(points);
    CadItem::setShape();
}

void CadRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    if( isSelected() || controlPointsGroup->controlPointSelected() )
        controlPointsGroup->setVisible(((CadScene *) scene())->isControlPointsOn());
    else
        controlPointsGroup->setVisible(false);

    QGraphicsPolygonItem::paint(painter,option,widget);
}

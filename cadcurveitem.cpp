#include "cadcurveitem.h"
#include <QPainter>
#include <qmath.h>
#include "qtransform.h"
#include "cadscene.h"
#include "qdebug.h"

CadCurveItem::CadCurveItem(CadType cadType)
    : CadItem(cadType)
{
    nOfPoints=0;
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable, true);
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    boundingCircle = new CadBoundingCircle(this);
    boundingCircle->setVisible(false);

    QColor color = Qt::black;
    setPen(QPen(color, 1));

    controlPointsGroup = new CadControlPointsItem();
    controlPointsGroup->setVisible(false);
    controlPointsGroup->setParentItem(this);
}

bool CadCurveItem::isFinished()
{
    if(nOfPoints==4)
    {
        setConstructed(true);
        setControlPointsItem();
//        controlPointsGroup->setPoints(getPointsPolygon());
        //        boundingCircle->setPoints(getPointsPolygon());
        return true;
    }
    else
        return false;
}

void CadCurveItem::addPoint(QPointF point)
{
    setSelected(true);
    if(nOfPoints==0)
    {
        pointPolygon<<point;
        pointPolygon<<point;
        pointPolygon<<point;
        pointPolygon<<point;
        setShape();
    }
    else if(nOfPoints==1)
    {
        pointPolygon[1]=point;
        pointPolygon[3]=point;
        setShape();
    }
    else
    {
        pointPolygon[nOfPoints]=point;
//        boundingCircle->setPoints(getPointsPolygon());
        setShape();
    }
    nOfPoints++;
}
void CadCurveItem::addTempPoint(QPointF point)
{
    if(nOfPoints==1)
    {
        pointPolygon[1]=point;
        pointPolygon[3]=point;
        setShape();
    }
    if(nOfPoints>1)
    {
        pointPolygon[nOfPoints]=point;
        setShape();
    }
}

QPolygonF CadCurveItem::polyToCurve(const QPolygonF &poly)
{
    QPolygonF polygon;
//    polygon<<p1<<QPointF(p1.x(),p2.y())<<p2<<QPointF(p2.x(),p1.y());
    return poly;
}

QGraphicsItem * CadCurveItem::getItem()
{
    return this;
}

void CadCurveItem::translate(QPointF modifier)
{
    QTransform transform;
    transform.translate(modifier.rx(), modifier.ry());
    QGraphicsItem::setTransform(transform,true);
}

void CadCurveItem::setShape(bool transform)
{
    if(transform)
        transformPoints();

    QPainterPath path;
    path.moveTo(points[0]);
    path.cubicTo(points.at(2),points.at(3),points.at(1));
    setPath(path);

    CadItem::setShape();
}

void CadCurveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    QColor color = Qt::red;
    setPen(QPen(color, 4));
    QGraphicsPathItem::paint(painter,option,widget);

    painter->setPen(QPen(Qt::black, 1));

    painter->drawLine(points.at(0),points.at(2));
    painter->drawLine(points.at(2),points.at(3));
    painter->drawLine(points.at(3),points.at(1));

    QVector<qreal> B;
    QPointF prevPoint = points.at(0);
    QPointF curPoint;
    for(qreal t = 0.01; t<1; t+=0.01)
    {
        B = calcB(t);
        curPoint = QPointF(0,0);
        for(int i=0;i<4;i++)
        {
            curPoint.setX(curPoint.x()+((QPointF)points[i]).x()*B[i]);
            curPoint.setY(curPoint.y()+((QPointF)points[i]).y()*B[i]);
        }
        painter->drawLine(prevPoint,curPoint);
        prevPoint = curPoint;
    }
    painter->drawLine(prevPoint,points.at(1));
}

QVector<qreal> CadCurveItem::calcB(qreal t) const
{
    QVector<qreal> res(4,0);
    res[0] = (1-t)*(1-t)*(1-t);
    res[2] = 3*t*(1-t)*(1-t);
    res[3] = 3*t*t*(1-t);
    res[1] = t*t*t;
    return res;
}

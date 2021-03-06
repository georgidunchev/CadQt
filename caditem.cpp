#include <QtGui>
#include "caditem.h"
#include "cadlineitem.h"
#include "cadrectitem.h"
#include <qmath.h>

CadItem::CadItem(CadType cadType)
{
    myCadType = cadType;

    constructed = false;
    nOfPoints=0;

    rotAngle = 0;
    scaleFactor = QPointF(1,1);

//    resetOriginPoint();

    qreal matrix[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    for(int i=0;i<3;i++)
        for(int j=0;j <3; j++)
            transformMatrix[i][j] = matrix[i][j];
}

QPolygonF CadItem::getPointsPolygon()
{
    return pointPolygon;
}
QPolygonF * CadItem::getPoints()
{
    return &points;
}

void CadItem::updateCurrentPoints(int id, QPointF newPoint)
{
    points[id] = newPoint;
    setShape(false);
}

void CadItem::updatePointsPolygon(int id, QPointF newPoint)
{
    //new stuff
//    qDebug()<<pointPolygon[id]<<originPoint<<newPoint<<
////            (newPoint.x()-originPoint.x())<<(pointPolygon[id].x()-originPoint.x())<<
//            QPointF((newPoint.x()-originPoint.x())/(pointPolygon[id].x()-originPoint.x())
//                   ,(newPoint.y()-originPoint.y())/(pointPolygon[id].y()-originPoint.y()));
//    scale(QPointF((newPoint.x()-originPoint.x())/(pointPolygon[id].x()-originPoint.x())
//                  ,(newPoint.y()-originPoint.y())/(pointPolygon[id].y()-originPoint.y())));
    ///newstuff

    qreal point[3][3] = {{newPoint.x(),0,0},{newPoint.y(),0,0},{1,0,0}};
    qreal a = transformMatrix[0][0];
    qreal b = transformMatrix[0][1];
    qreal c = transformMatrix[0][2];
    qreal d = transformMatrix[1][0];
    qreal e = transformMatrix[1][1];
    qreal f = transformMatrix[1][2];
    qreal g = transformMatrix[2][0];
    qreal h = transformMatrix[2][1];
    qreal k = transformMatrix[2][2];
    qreal Z = a*(e*k - f*h) + b*(f*g-k*d) + c*(d*h-e*g);
    qreal matrix[3][3] = {{e*k/Z - f*h/Z,c*h/Z - b*k/Z,b*f/Z - c*e/Z},
                          {f*g/Z - d*k/Z,a*k/Z - c*g/Z,c*d/Z - a*f/Z},
                          {d*h/Z - e*g/Z,b*g/Z - a*h/Z,a*e/Z - b*d/Z}};
    multiply(matrix, point);
    pointPolygon[id] =  QPointF(matrix[0][0],matrix[1][0]);



    setShape();
}

void CadItem::setOriginPoint()
{
    originPoint = boundingCircle->getCentrePoint();
}
QPointF CadItem::getOriginPoint() const
{
//    return originPoint;
    return controlPointsGroup->getOriginPoint();
}
void CadItem::resetOriginPoint()
{
    originPoint = boundingCircle->getCentrePoint();
    controlPointsGroup->updateOriginPoint(originPoint);
}

void CadItem::updateOriginPoint(QPointF newPoint)
{
    originPoint = newPoint;
}

void CadItem::setBoundingCircle(bool b)
{
    bBoundingCircle=b;
}

void CadItem::setControlPoints(bool b)
{
    bControlPoints=b;
}

void CadItem::addPoint(QPointF point)
{

}

void CadItem::addTempPoint(QPointF point)
{

}

bool CadItem::isFinished()
{
        return false;
}

QGraphicsItem * CadItem::getItem()
{
    return 0;
}

void CadItem::translate(QPointF modifier, bool temporal)
{

//    QTransform transform;
//    transform.translate(modifier.rx(), modifier.ry());
//    QGraphicsItem::setTransform(transform,true);

    if(temporal)
    {
        for(int i=0;i<3;i++)
            for(int j=0;j <3; j++)
                tempTransformMatrix[i][j] = transformMatrix[i][j];
    }

    qreal trans[3][3] = {{1,0,0},{0,1,0},{0,0,1}};

    trans[0][2] = modifier.rx();
    trans[1][2] = modifier.ry();

    multiply(trans,transformMatrix);

    for(int i=0;i<3;i++)
        for(int j=0;j <3; j++)
            transformMatrix[i][j] = trans[i][j];

    setShape();
    updateControlPointsItem();
    if(temporal)
    {
        for(int i=0;i<3;i++)
            for(int j=0;j <3; j++)
                transformMatrix[i][j] = tempTransformMatrix[i][j] ;
    }
}

void CadItem::rotate(qreal angle, bool temporal)//qreal angle)
{
    rotAngle = angle;
    if(rotAngle>=360) rotAngle-=360;

    if(temporal)
    {
        for(int i=0;i<3;i++)
            for(int j=0;j <3; j++)
                tempTransformMatrix[i][j] = transformMatrix[i][j];
    }

    qreal matrix[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    qreal revTrans[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    qreal rotate[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    qreal trans[3][3] = {{1,0,0},{0,1,0},{0,0,1}};

    revTrans[0][2] = -(trans[0][2] = originPoint.rx());
    revTrans[1][2] = -(trans[1][2] = originPoint.ry());

//    qreal PI = 3.14159265;
    rotate[0][0]=rotate[1][1]=cos(rotAngle/**PI/180*/);
    rotate[0][1]=-(rotate[1][0]=sin(rotAngle/**PI/180*/));

    multiply(matrix,trans);
    multiply(matrix,rotate);
    multiply(matrix,revTrans);
    multiply(matrix,transformMatrix);

    for(int i=0;i<3;i++)
        for(int j=0;j <3; j++)
            transformMatrix[i][j] = matrix[i][j];

    setShape();
    updateControlPointsItem();
    if(temporal)
    {
        for(int i=0;i<3;i++)
            for(int j=0;j <3; j++)
                transformMatrix[i][j] = tempTransformMatrix[i][j] ;
    }
}

void CadItem::scale(QPointF factor, bool temporal)
{
    if(temporal)
    {
        for(int i=0;i<3;i++)
            for(int j=0;j <3; j++)
                tempTransformMatrix[i][j] = transformMatrix[i][j];
    }

    scaleFactor.setX(factor.rx());
    scaleFactor.setY(factor.ry());

    qreal matrix[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    qreal revTrans[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    qreal scale[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    qreal trans[3][3] = {{1,0,0},{0,1,0},{0,0,1}};

    revTrans[0][2] = -(trans[0][2] = originPoint.rx());
    revTrans[1][2] = -(trans[1][2] = originPoint.ry());

    scale[0][0] = scaleFactor.rx();
    scale[1][1] = scaleFactor.ry();

    multiply(matrix,trans);
    multiply(matrix,scale);
    multiply(matrix,revTrans);
    multiply(matrix,transformMatrix);

    for(int i=0;i<3;i++)
        for(int j=0;j <3; j++)
            transformMatrix[i][j] = matrix[i][j];

    setShape();
    updateControlPointsItem();

    if(temporal)
    {
        for(int i=0;i<3;i++)
            for(int j=0;j <3; j++)
                transformMatrix[i][j] = tempTransformMatrix[i][j] ;
    }
}

void CadItem::setTempTransformations(bool b)
{
    for(int i=0;i<3;i++)
        for(int j=0;j <3; j++)
            tempTransformMatrix[i][j] = transformMatrix[i][j];
}

void CadItem::setShape(bool transform)
{
    if(isConstructed())
        boundingCircle->setPoints(points);
}

void CadItem::transformPoints()
{
    points.clear();

    foreach(QPointF point, pointPolygon)
    {
        points << transformPoint(point);
    }
}

void CadItem::multiply(qreal matrix[3][3], qreal multiplier[3][3])
{
    qreal newMatrix[3][3] ={{matrix[0][0],matrix[0][1],matrix[0][2]},
                            {matrix[1][0],matrix[1][1],matrix[1][2]},
                            {matrix[2][0],matrix[2][1],matrix[2][2]}};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j <3; j++)
        {
            qreal tmp=0;
            for(int k=0;k<3;k++)
            {
                qreal tmp1 = newMatrix[i][k];
                qreal tmp2 = multiplier[k][j];
                qreal tmp3 = tmp1*tmp2;
                tmp+=tmp3;
            }
            matrix[i][j] = tmp;
        }
    }
}

QPointF CadItem::transformPoint(const QPointF &point/*, qreal transformMatrix[3][3]*/)
{
    qreal newPoint[3][3] = {{point.x(),0,0},{point.y(),0,0},{1,0,0}};
    qreal matrix[3][3] = {{transformMatrix[0][0],transformMatrix[0][1],transformMatrix[0][2]},
                          {transformMatrix[1][0],transformMatrix[1][1],transformMatrix[1][2]},
                          {0,0,1}};
    multiply(matrix, newPoint);
    return QPointF(matrix[0][0],matrix[1][0]);
}

void CadItem::setControlPointsItem()
{
    controlPointsGroup->setPoints(points,originPoint);
    controlPointsGroup->setOriginPoint(originPoint);
}

void CadItem::updateControlPointsItem()
{
    controlPointsGroup->updatePoints(points,originPoint);
}

void CadItem::setConstructed(bool b)
{
    if(b)
    {
        boundingCircle->setPoints(points);
        setOriginPoint();
    }
    //    boundingCircle->getCentrePoint();

    constructed = b;
}

bool CadItem::isConstructed()
{
    return constructed;
}

#include "cadboundingcircle.h"
#include <QtAlgorithms>
#include "qdebug.h"
#include <QPen>
#include "math.h"

CadBoundingCircle::CadBoundingCircle(QGraphicsItem * parent)
{
    setParentItem(parent);
//    setPen(pen());
    QColor color = Qt::red;
    setPen(QPen(color, 2));

    color = Qt::blue;
    pI1 = new QGraphicsPathItem(this);
    pI1->setPen(QPen(color,2));

    color = Qt::green;
    pI2 = new QGraphicsPathItem(this);
    pI2->setPen(QPen(color,2));
//    circlePath->setParentItem(parentItem());
}

void CadBoundingCircle::setPoints(const QPolygonF &newPoints)
{
    points = newPoints;
//    setRect(points.boundingRect());
}

void CadBoundingCircle::addPoint(const QPointF &newpoint)
{
    points<<newpoint;
    sortPoints();
    if(points.size()>=3)
    {
        calcConvexHull();
        findBoundingCircle();
        QPainterPath path1,path2,path3;

        path1.addPolygon(convexHull);
        path1.closeSubpath();
        setPath(path1);

        path2.addPolygon(cen);
        path2.closeSubpath();
        pI1->setPath(path2);

        QRectF re(centrePoint.x()-radius,centrePoint.y()-radius,radius*2,radius*2);
        path3.addEllipse(re);
//        QRectF re(centrePoint.x(),centrePoint.y(),radius,radius);
//        path3.addRect(re);
        pI2->setPath(path3);

//        circlePath->setPen(QPen(Qt::blue,2));
                //        path.addEllipse(QRectF(convexHull.boundingRect()));
//                setPath(path);
        //                setPolygon(convexHull);
    }
    //    setRect(points.boundingRect());
}

qreal CadBoundingCircle::position(const QPointF & p1, const QPointF & p2, const QPointF & p3)
{
//    QPointF p1 = firstPoint;
    return ((p2.x() - p1.x())*(p3.y() - p1.y()) - (p3.x() - p1.x())*(p2.y() - p1.y()));
}

int CadBoundingCircle::findFirstPoint()
{
    QPointF p;
    int i=0, j=0;
    foreach(QPointF item, points)
    {
        if(i==0)
            p=item;
        else
        {
            if( (item.y()<p.y()) ||
                (item.y()==p.y() && item.x()>p.x()) )
            {
                j=i;
            }
        }
        i++;
    }
    return j;
}

void CadBoundingCircle::sortPoints()
{
    int ind = findFirstPoint();
    QPointF firstPoint = points.at(ind);
    points.remove(ind);
    points.push_front(firstPoint);

    int size = points.size();
    for(int i = 1; i < size-1; i++)
    {
//        if(i != ind)
        for(int j = i+1; j<size; j++)
        {
            if(/*(j != ind) &&*/ (position(firstPoint,points.at(i),points.at(j)) < 0))
            {
//                QPointF bla1 = firstPoint;
//                QPointF bla2 = points.at(i);
//                QPointF bla3 = points.at(j);
//                qreal bla4 =     position(firstPoint,points.at(i),points.at(j));
                QPointF tmp = points.at(i);
                points.replace(i, points.at(j));
                points.replace(j, tmp);
            }
        }
    }
}

void CadBoundingCircle::calcConvexHull()
{
    convexHull.clear();
    convexHull<<points.at(0)<<points.at(1);
    int size = points.size();
    for(int i = 2; i < size; i++)
    {
        for(int j=convexHull.size()-1; j>=0; j--)
        {
//            QPointF bla1 = convexHull.at(j-1);
//            QPointF bla2 = convexHull.at(j);
//            QPointF bla3 = points.at(i);
//            qreal bla4 = position(convexHull.at(j-1), convexHull.at(j), points.at(i));
            if(position(convexHull.at(j-1), convexHull.at(j), points.at(i)) > 0)
            {
                convexHull<<points.at(i);
                break;
            }
            else
                convexHull.pop_back();
        }
    }
}

int CadBoundingCircle::calcLineLength(const QPointF &A, const QPointF &B)
{
    int x = A.x()-B.x();
    int y = A.y()-B.y();
    return x*x+y*y;
}

double CadBoundingCircle::calcRadius(const QPointF & A, const QPointF & B, const QPointF & C)
{
    double a = calcLineLength(C,B);
    double b = calcLineLength(A,C);
    double c = calcLineLength(A,B);
    double S = a*b*c;
    S = S / ((a+b+c)*(a+b+c) - 2*(a*a+b*b+c*c));
    if(isObtuse(A,B,C)) S *= -1;
    return S;
}

//bool CadBoundingCircle::compRadius(const QPointF & A, const QPointF & B, const QPointF & C1, const QPointF & C2)
//{
//    return calcRadius(A,B,C1) < calcRadius(A,B,C2);
//}

//bool CadBoundingCircle::compRadius(const QPointF & A, const QPointF & B, int R, const QPointF & C2)
//{
//    return R < calcRadius(A,B,C2);
//}

bool CadBoundingCircle::isObtuse(const QPointF & A, const QPointF & B, const QPointF & C)
{
    double a = calcLineLength(C,B);
    double b = calcLineLength(A,C);
    double c = calcLineLength(A,B);
    double res = ( a + b - c );
    bool r = (res <= 0 );
    return r;
}

int CadBoundingCircle::triangleHasObtuse(const QPointF & A, const QPointF & B, const QPointF & C)
{
    double a = calcLineLength(C,B);
    double b = calcLineLength(A,C);
    double c = calcLineLength(A,B);
    if (( a + b - c ) <= 0 )
        return 1;
    if (( b + c - a ) <= 0 )
        return 2;
    if (( c + a - b ) <= 0 )
        return 3;
    return 0;
}

QPointF CadBoundingCircle::findCentrePoint(const QPointF & A, const QPointF & B)
{
    int x = B.x() + (A.x()-B.x())/2;
    int y = B.y() + (A.y()-B.y())/2;
    return QPointF(x,y);
}

QPointF CadBoundingCircle::findCentrePoint(const QPointF & A, const QPointF & B, const QPointF & C)
{
//    QPointF a = findCentrePoint(C,B);
//    QPointF b = findCentrePoint(A,C);

//    qreal Sam =  ( (B.x()-C.x()) / ( C.y()-B.y()) );
//    qreal t1 =  C.y()-B.y();
//    qreal t2 =  B.x()-C.x();
//    qreal Sac = a.y() - Sam * a.x();

//    qreal Sbm = (A.x()-C.x()) / ( C.y()-A.y());
//    qreal t3 =  C.y()-A.y();
//    qreal t4 =  A.x()-C.x();
//    qreal Sbc = b.y() - Sbm * b.x();

//    QPointF res;
//    res.setX((Sbc-Sac)/(Sbm-Sam));
//    res.setY(res.x()*Sam + Sac);
//    return res;

    qreal a = C.x() - A.x();
    qreal b = C.y() - A.y();
    qreal c = C.x()*C.x() - A.x()*A.x() + C.y()*C.y() - A.y()*A.y();
    qreal d = B.x() - A.x();
    qreal e = B.y() - A.y();
    qreal f = B.x()*B.x() - A.x()*A.x() + B.y()*B.y() - A.y()*A.y();
    qreal g = 2*((b*d)-(a*e));

    QPointF res;
    res.setX((e*c-b*f)/(-g));
    res.setY((d*c-a*f)/(g));
    return res;
}

void CadBoundingCircle::findBoundingCircle()
{
    int size = convexHull.size();
    double radius;
    int fP=0,sP=1;

    while(1)
    {
        int angleInd;
        if(fP != 0 && sP != 0)            angleInd=0;
        else if(fP != 1 && sP != 1)            angleInd=1;
        else            angleInd=2;

        radius = calcRadius(convexHull.at(fP),convexHull.at(sP),convexHull.at(angleInd));
        for(int i = 0; i < size; i++)
            if ( (i != fP) && (i != sP) && (i != angleInd))
            {
                double newRadius = calcRadius(convexHull.at(fP),convexHull.at(sP),convexHull.at(i));
                if(radius < newRadius)
                {
                    radius = newRadius;
                    angleInd = i;
                }
            }

        if(isObtuse(convexHull.at(fP),convexHull.at(sP),convexHull.at(angleInd)))
        {
            cen.clear();
            cen<<convexHull.at(fP)<<convexHull.at(sP);
            centrePoint = findCentrePoint(convexHull.at(fP),convexHull.at(sP));
            this->radius = sqrt(calcLineLength(centrePoint,convexHull.at(fP)));
            return;
        }

        int S = triangleHasObtuse(convexHull.at(fP),convexHull.at(sP),convexHull.at(angleInd));
        switch (S)
        {
        case 0:
            {
                cen.clear();
                cen<<convexHull.at(fP)<<convexHull.at(sP)<<convexHull.at(angleInd);
                centrePoint = findCentrePoint(convexHull.at(fP),convexHull.at(sP),convexHull.at(angleInd));
                this->radius = sqrt(calcLineLength(centrePoint,convexHull.at(fP)));
                return;
            }
            break;
        case 1:
            {
                // this should not be possible
            }
            break;
        case 2:
            {
                fP = angleInd;
                //sP=sP;
            }
            break;
        case 3:
            {
                sP = angleInd;
                //fP=fP;
            }
            break;
        }
    }
}






//void CadBoundingCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
////    setRect(points->boundingRect());
//    QGraphicsEllipseItem::paint(painter,option,widget);
//}

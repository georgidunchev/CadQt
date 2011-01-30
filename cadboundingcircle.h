#ifndef CADBOUNDINGCIRCLE_H
#define CADBOUNDINGCIRCLE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>

class CadBoundingCircle : public QGraphicsPathItem //QGraphicsEllipseItem
{
public:
//    CadBoundingCircle(QPolygonF * newPoints);
    CadBoundingCircle(QGraphicsItem * parent = 0);
    void setPoints(const QPolygonF & newPoints);
    void addPoint(const QPointF & newpoint);
    QPointF getCentrePoint();

//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPolygonF points,convexHull,cen,bC;
//    int firstPoint;

    qreal position(const QPointF & p1, const QPointF & p2, const QPointF & p3);
    int findFirstPoint();
    void sortPoints();
    void calcConvexHull();
    int calcLineLength(const QPointF & A, const QPointF & B);
    double calcRadius(const QPointF & A, const QPointF & B, const QPointF & C);
//    bool compRadius(const QPointF & A, const QPointF & B, const QPointF & C1, const QPointF & C2);
//    bool compRadius(const QPointF & A, const QPointF & B, int R, const QPointF & C2);
    bool isObtuse(const QPointF & A, const QPointF & B, const QPointF & C);
    int triangleHasObtuse(const QPointF & A, const QPointF & B, const QPointF & C);
    QPointF findCentrePoint(const QPointF & A, const QPointF & B);
    QPointF findCentrePoint(const QPointF & A, const QPointF & B, const QPointF & C);
    void findBoundingCircle();

    QGraphicsPathItem * pI1, *pI2;
    double radius;
    QPointF centrePoint;


};

#endif // CADBOUNDINGCIRCLE_H

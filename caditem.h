#ifndef CADITEM_H
#define CADITEM_H

#include <QGraphicsItem>
#include "cadboundingcircle.h"
#include "cadcontrolpointsitem.h"
//#include "cadscene.h"
//#include "mainwindow.h"

class CadItem
{
public:
    enum CadType { Line, Curve, Rect, Polygon, Step, Conditional, StartEnd, Io };

    CadItem(CadType cadType);

    enum { Type = QGraphicsItem::UserType};
    int type() const
        { return Type; }

    QPolygonF getPointsPolygon();
    QPolygonF * getPoints();
    virtual void updateCurrentPoints(int id, QPointF newPoint);
    virtual void updatePointsPolygon(int id, QPointF newPoint);
    virtual void updateOriginPoint(QPointF newPoint);
    virtual void resetOriginPoint();
    virtual void setOriginPoint();

    virtual void setBoundingCircle(bool b);
    virtual void setControlPoints(bool b);

    virtual bool isFinished();
    virtual void addPoint(QPointF point);
    virtual void addTempPoint(QPointF point);

    virtual QGraphicsItem * getItem();

    virtual void translate(QPointF modifier);
    virtual void rotate(qreal angle);
    virtual void scale(QPointF factor);

    virtual void setShape(bool transform = true);

    void setConstructed(bool b);
    bool isConstructed();

protected:
    CadType myCadType;
    QPolygonF pointPolygon; // original points
    QPolygonF points; // current points
    qreal rotAngle;
    QPointF scaleFactor;
    qreal transformMatrix[3][3];
//    QVector2D<qreal> multiplier();
    QPointF originPoint;
    int nOfPoints;

    void transformPoints();
    void multiply(qreal matrix[3][3], qreal multiplier[3][3]);
    QPointF transformPoint(const QPointF & point);

    void setControlPointsItem();
    void updateControlPointsItem();


    bool bBoundingCircle;
    CadBoundingCircle * boundingCircle;

    bool bControlPoints;
    CadControlPointsItem * controlPointsGroup;

private:
    bool constructed;
};

#endif // CADITEM_H


#ifndef CADCONTROLPOINTSGROUP_H
#define CADCONTROLPOINTSGROUP_H

#include <QGraphicsItemGroup>

class CadControlPointsGroup : public QGraphicsItemGroup
{
public:
    CadControlPointsGroup();
    void setPoints(QPolygonF * newPoints);

private:
    QPolygonF * points;
};

#endif // CADCONTROLPOINTSGROUP_H

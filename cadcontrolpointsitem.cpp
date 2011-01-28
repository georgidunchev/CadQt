#include "cadcontrolpointsitem.h"
//#include "mainwindow.h"
#include <QGraphicsScene>
#include <QDebug>

CadControlPointsItem::CadControlPointsItem()
{
    QGraphicsItem::setFlag(QGraphicsItemGroup::ItemIsMovable, true);
    QGraphicsItem::setFlag(QGraphicsItemGroup::ItemIsSelectable, true);

//    mw =  (MainWindow * ) scene()->parent();
//    ci = mw->castQGraphicsItemToCadItem(parentItem());
}

void CadControlPointsItem::setPoints(const QPolygonF & newPoints)
{
    points = newPoints;
    CadControlPointRectItem * rectItem;

    for(int i = 0; i<points.size();i++)
    {
        rectItem = new CadControlPointRectItem(i,points.value(i),parentItem());
        controlPointItems.append(rectItem);
    }
}

void CadControlPointsItem::updatePoints(const QPolygonF & newPoints)
{
    if(points.size()!=newPoints.size())
        return;

    points = newPoints;

    for(int i = 0; i<points.size();i++)
    {
                controlPointItems.at(i)->setPoint(points.at(i));
    }
}

void CadControlPointsItem::setVisible(bool visible)
{
    for(int i =0; i<controlPointItems.size();i++)
    {
        controlPointItems.at(i)->setVisible(visible);
    }
    QGraphicsItem::setVisible(visible);
}

bool CadControlPointsItem::controlPointSelected()
{
    foreach( CadControlPointRectItem * item, controlPointItems )
    {
        if (item->isSelected())
            return true;
    }
    return false;
}

#include "cadcontrolpointsitem.h"
#include "cadcontrolpointrectitem.h"
#include "mainwindow.h"
#include "caditem.h"
#include <QGraphicsScene>
#include <QDebug>

CadControlPointsItem::CadControlPointsItem(QGraphicsItem *parent) : QGraphicsItemGroup(parent)
{
    QGraphicsItem::setFlag(QGraphicsItemGroup::ItemIsMovable, true);
    QGraphicsItem::setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
}

void CadControlPointsItem::setPoints(const QPolygonF &newPoints, const QPointF &newOriginPoint)
{
    points = newPoints;
    CadControlPointRectItem * rectItem;
    MainWindow * mw =  (MainWindow * ) scene()->parent();
    CadItem * ci = mw->castQGraphicsItemToCadItem(parentItem());

    for(int i = 0; i<points.size();i++)
    {
        rectItem = new CadControlPointRectItem(i, points.value(i), ci, parentItem());
        controlPointItems.append(rectItem);
    }

//    originPoint = new CadControlPointRectItem(0,newOriginPoint, ci, parentItem(),false);
}

void CadControlPointsItem::setOriginPoint(const QPointF &newOriginPoint)
{
    MainWindow * mw =  (MainWindow * ) scene()->parent();
    CadItem * ci = mw->castQGraphicsItemToCadItem(parentItem());
    originPoint = new CadControlPointRectItem(0,newOriginPoint, ci, parentItem(),false);
}

void CadControlPointsItem::updatePoints(const QPolygonF &newPoints, const QPointF &originPoint)
{
    if(points.size()!=newPoints.size())
        return;

    points = newPoints;

    for(int i = 0; i<points.size();i++)
    {
        controlPointItems.at(i)->setPoint(points.at(i));
    }
}

void CadControlPointsItem::updateOriginPoint(const QPointF &newOriginPoint)
{
    originPoint->setPoint(newOriginPoint);
}

QPointF CadControlPointsItem::getOriginPoint() const
{
    return originPoint->scenePos();
}

void CadControlPointsItem::setVisible(bool visible)
{
    for(int i =0; i<controlPointItems.size();i++)
    {
        controlPointItems.at(i)->setVisible(visible);
    }
//    originPoint->setVisible(visible);
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

#include "cadscene.h"
#include "caditem.h"
//#include "cadboundingcircle.h"
#include <QtGui>

CadScene::CadScene(QObject *parent)
    : QGraphicsScene(parent)
{
    bBoundingCircle = false;
    bControlPoints = true;
    bAutoOriginPoint = true;
//    myMode = MoveItem;
    myTransMode = None;
    myItemType = CadItem::Step;
    line = 0;
}

void CadScene::setMode(Mode mode)
{
    myMode = mode;
}

int CadScene::getMode()
{
    return myMode;
}

void CadScene::setTransformationMode(transformationMode mode)
{
    myTransMode = mode;
}

uint CadScene::getTransMode()
{
    return myTransMode;
}

void CadScene::setItemType(CadItem::CadType type)
{
    myItemType = type;
}

void CadScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    clearSelection();
    update(sceneRect());

    if (mouseEvent->button() == Qt::LeftButton)
    {
        switch (myMode)
        {
        case Select:
            {
                QGraphicsScene::mousePressEvent(mouseEvent);
                return;
            }
            break;
        case Drawing:
            {
                if(tempItem!=0)
                {
                    switch (myItemType)
                    {
                    case (CadItem::Line):
                        {
                            tempItem->addPoint(mouseEvent->scenePos());
                            if(tempItem->isFinished())
                            {
                                emit itemInserted();
                            }
                        }
                        break;
                    case (CadItem::Curve):
                        {
                            tempItem->addPoint(mouseEvent->scenePos());
                            if(tempItem->isFinished())
                                emit itemInserted();
                        }
                        break;
                    case (CadItem::Rect):
                        {
                            tempItem->addPoint(mouseEvent->scenePos());
                            if(tempItem->isFinished())
                                emit itemInserted();
                        }
                        break;
                    case (CadItem::Polygon):
                        {
                            tempItem->addPoint(mouseEvent->scenePos());
                        }
                        break;
                    default:
                        ;
                    }
                }
            }
            break;
        case InsertLine:
            {
                emit setTracking(true);

                myItemType = CadItem::Line;
                myMode = Drawing;
                tempItem = new CadLineItem(myItemType);
                tempItem->addPoint(mouseEvent->scenePos());
                addItem(tempItem->getItem());
                //                QGraphicsScene::setsetMouseTracking(true);
                //                addItem(tempItem);

                //            myItemType = CadItem::Conditional;
                //            item = new CadItem(myItemType, myItemMenu);
                //            item->setBrush(myItemColor);
                //            addItem(item);
                //            item->setPos(mouseEvent->scenePos());
                //            emit itemInserted(tempItem);
            }
            break;
        case InsertCurve:
            {
                myItemType = CadItem::Curve;
                myMode = Drawing;
                tempItem = new CadCurveItem(myItemType);
                tempItem->addPoint(mouseEvent->scenePos());
                addItem(tempItem->getItem());
                emit setTracking(true);
            }
            break;
        case InsertRect:
            {
                myItemType = CadItem::Rect;
                myMode = Drawing;
                tempItem = new CadRectItem(myItemType);
                tempItem->addPoint(mouseEvent->scenePos());
                addItem(tempItem->getItem());
                emit setTracking(true);
            }
            break;
        case InsertPolygon:
            {
                myItemType = CadItem::Polygon;
                myMode = Drawing;
                tempItem = new CadPolyItem(myItemType);
//                tempItem->setConstructed(true);
                tempItem->addPoint(mouseEvent->scenePos());
                addItem(tempItem->getItem());

                emit setTracking(true);
            }
            break;
        default:
            ;
        }
    }

    if (mouseEvent->button() == Qt::RightButton)
    {
        if(myMode==Drawing)
        {
            if(tempItem!=0)
            {
                switch (myItemType)
                {
                case (CadItem::Line):
                    {
                        tempItem->addPoint(mouseEvent->scenePos());
                        if(tempItem->isFinished())
                            emit itemInserted();
                    }
                    break;
                case (CadItem::Rect):
                    {
                        tempItem->addPoint(mouseEvent->scenePos());
                        if(tempItem->isFinished())
                            emit itemInserted();
                    }
                    break;
                case (CadItem::Polygon):
                    {
                        tempItem->addPoint(mouseEvent->scenePos());
                        if(tempItem->isFinished())
                            emit itemInserted();
                    }
                default:
                    ;
                }
            }
        }
        else
            QGraphicsScene::mousePressEvent(mouseEvent);

    }
//    QGraphicsScene::mousePressEvent(mouseEvent);
}

void CadScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    if (myMode == Drawing)
    {// && tempItem != 0) {
        switch (myItemType)
        {
        case (CadItem::Line):
            {
                tempItem->addTempPoint(mouseEvent->scenePos());
            }
            break;
        case (CadItem::Curve):
            {
                tempItem->addTempPoint(mouseEvent->scenePos());
            }
            break;
        case (CadItem::Rect):
            {
                tempItem->addTempPoint(mouseEvent->scenePos());
            }
            break;
        case (CadItem::Polygon):
            {
                tempItem->addTempPoint(mouseEvent->scenePos());
            }
            break;
        default:
            ;
        }
//        if(bBoundingCircle)
//        {
//            showBoundingCircle(tempItem);
//        }
    }
    else if (myMode == Select/*MoveItem*/)
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);

    }
}

void CadScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
     QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void CadScene::setBoundingCircle(bool b)
{
    bBoundingCircle=b;
}
bool CadScene::isBoundingCircleOn()
{
    return bBoundingCircle;
}

void CadScene::setControlPoints(bool b)
{
    bControlPoints=b;
}

bool CadScene::isControlPointsOn()
{
    return bControlPoints;
}

bool CadScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}

#include "cadscene.h"
#include "caditem.h"
//#include "cadboundingcircle.h"
#include <QtGui>

CadScene::CadScene(/*QMenu *itemMenu,*/ QObject *parent)
    : QGraphicsScene(parent)
{
    bBoundingCircle = false;
    bControlPoints = false;
    bAutoOriginPoint = true;
//    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = CadItem::Step;
    line = 0;
    //    textItem = 0;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;
}
//! [0]

//! [1]
void CadScene::setLineColor(const QColor &color)
{
    myLineColor = color;
    //    if (isItemChange(Arrow::Type)) {
    //        Arrow *item =
    //            qgraphicsitem_cast<Arrow *>(selectedItems().first());
    //        item->setColor(myLineColor);
    //        update();
    //    }
}

void CadScene::setItemColor(const QColor &color)
{
    myItemColor = color;
    //    if (isItemChange(CadItem::Type)) {
    //        CadItem *item =
    //            qgraphicsitem_cast<CadItem *>(selectedItems().first());
    //        item->setBrush(myItemColor);
    //    }
}

void CadScene::setMode(Mode mode)
{
    myMode = mode;
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
//                myMode = MoveItem;
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
                                //                            myMode=Select;
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
    /*  if (line != 0 && myMode == InsertCurve) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;
//! [11] //! [12]

//        if (startItems.count() > 0 && endItems.count() > 0 &&
//            startItems.first()->type() == CadItem::Type &&
//            endItems.first()->type() == CadItem::Type &&
//            startItems.first() != endItems.first()) {
//            CadItem *startItem =
//                qgraphicsitem_cast<CadItem *>(startItems.first());
//            CadItem *endItem =
//                qgraphicsitem_cast<CadItem *>(endItems.first());
//            Arrow *arrow = new Arrow(startItem, endItem);
//            arrow->setColor(myLineColor);
//            startItem->addArrow(arrow);
//            endItem->addArrow(arrow);
//            arrow->setZValue(-1000.0);
//            addItem(arrow);
//            arrow->updatePosition();
//        }
    }
//! [12] //! [13]
    line = 0;*/
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void CadScene::setBoundingCircle(bool b)
{
    bBoundingCircle=b;
//    if(bBoundingCircle==false)
//    {
        //remove bounding circle
//        removeItem(boundingCircle);
//    }
//    if(myMode==Drawing)
//    {
//        showBoundingCircle(tempItem);
//    }
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

//void CadScene::setAutoOriginPoint()
//{
//    selectedItems().first()->
//}
//bool CadScene::isAutoOriginPointOn()
//{
//    return bAutoOriginPoint;
//}

//void CadScene::showBoundingCircle(CadItem *item)
//{
////    bBoundingCircle=true;
//    //create bounding circle
////    boundingCircle = new CadBoundingCircle(item);
////    addItem(boundingCircle);
//}

bool CadScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}
//! [14]

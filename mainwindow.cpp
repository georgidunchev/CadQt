#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cadscene.h"
//#include "caditem.h"
#include "cadcontrolpointrectitem.h"
#include <QtGui>
#include <QLabel>
#include <QTransform>

const int InsertTextButton = 10;

MainWindow::MainWindow()
{
    createActions();
//    createToolBox();
    createMenus();

    scene = new CadScene(/*itemMenu, */this);
    scene->setSceneRect(QRectF(0, 0, 1000, 1000));
    connect(scene, SIGNAL(itemInserted()), this, SLOT(itemInserted()));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)), this, SLOT(itemSelected(QGraphicsItem*)));
    connect(scene, SIGNAL(setTracking(bool)), this, SLOT(setTracking(bool)));


    createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;
//    layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
//    view->setMouseTracking(true);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("CadQT"));
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::backgroundButtonGroupClicked(QAbstractButton *button)
{
    QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
    foreach (QAbstractButton *myButton, buttons) {
    if (myButton != button)
        button->setChecked(false);
    }
//    QString text = button->text();
//    if (text == tr("Blue Grid"))
//        scene->setBackgroundBrush(QPixmap(":/images/background1.png"));
//    else if (text == tr("White Grid"))
//        scene->setBackgroundBrush(QPixmap(":/images/background2.png"));
//    else if (text == tr("Gray Grid"))
//        scene->setBackgroundBrush(QPixmap(":/images/background3.png"));
//    else
//        scene->setBackgroundBrush(QPixmap(":/images/background4.png"));

//    scene->update();
    view->update();
}

void MainWindow::buttonGroupClicked(int id)
{
//    QList<QAbstractButton *> buttons = buttonGroup->buttons();
//    foreach (QAbstractButton *button, buttons) {
//    if (buttonGroup->button(id) != button)
//        button->setChecked(false);
//    }
//    if (id != InsertTextButton) {
//        scene->setMode(CadScene::InsertText);
//    } else {
//        scene->setItemType(CadItem::CadType(id));
//        scene->setMode(CadScene::Mode(id));
//        scene->setMode(CadScene::Mode(0));
        scene->setMode(CadScene::Mode(buttonGroup->checkedId()));
//    }
}

void MainWindow::deleteItem()
{
//    foreach (QGraphicsItem *item, scene->selectedItems()) {
//        if (item->type() == Arrow::Type) {
//            scene->removeItem(item);
//            Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
//            arrow->startItem()->removeArrow(arrow);
//            arrow->endItem()->removeArrow(arrow);
//            delete item;
//        }
//    }

    foreach (QGraphicsItem *item, scene->selectedItems()) {
//         if (item->type() == CadItem::Type) {
//             qgraphicsitem_cast<CadItem *>(item)->removeArrows();
//         }
         scene->removeItem(item);
         delete item;
     }
}

void MainWindow::pointerGroupClicked(int)
{
    scene->setMode(CadScene::Mode(pointerTypeGroup->checkedId()));
}

/*void MainWindow::buttonGroupClicked(int)
{
    //scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}*/

void MainWindow::translateItem()
{
    if (scene->selectedItems().isEmpty())        return;
    CadItem * item = castQGraphicsItemToCadItem(scene->selectedItems().first());
    if(item) item->translate(QPointF(10,10));
}
void MainWindow::rotateItem()
{
    if (scene->selectedItems().isEmpty())        return;
    CadItem * item = castQGraphicsItemToCadItem(scene->selectedItems().first());
    if(item) item->rotate(60);
}
void MainWindow::scaleItem()
{
    if (scene->selectedItems().isEmpty())        return;
    CadItem * item = castQGraphicsItemToCadItem(scene->selectedItems().first());
    if(item) item->scale(QPointF(0.7,0.5));
}

void MainWindow::setBoundingCircle(bool b)
{
    scene->setBoundingCircle(b);
    scene->update(scene->sceneRect());
}

void MainWindow::showControlPoints(bool b)
{
    scene->setControlPoints(b);
    scene->update(scene->sceneRect());
//    if (scene->selectedItems().isEmpty())        return;
//    castQGraphicsItemToCadItem(scene->selectedItems().first())->scale(QPointF(0.7,0.5));
}

//void MainWindow::sendToBack()
//{
////    if (scene->selectedItems().isEmpty())
////        return;

////    QGraphicsItem *selectedItem = scene->selectedItems().first();
////    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

////    qreal zValue = 0;
////    foreach (QGraphicsItem *item, overlapItems) {
////        if (item->zValue() <= zValue &&
////            item->type() == CadItem::Type)
////            zValue = item->zValue() - 0.1;
////    }
////    selectedItem->setZValue(zValue);
//}

void MainWindow::itemInserted()
{
    buttonGroup->button(int(CadScene::Select))->setChecked(true);
    scene->setMode(CadScene::Select);
    setTracking(false);
//    tuk gyrmi!
//    buttonGroup->button(int(item->cadType()))->setChecked(false);
}
void MainWindow::setTracking(bool b)
{
    view->setMouseTracking(b);
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
//    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
//    QMatrix oldMatrix = view->matrix();
//    view->resetMatrix();
//    view->translate(oldMatrix.dx(), oldMatrix.dy());
//    view->scale(newScale, newScale);
}

void MainWindow::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
//    fillColorToolButton->setIcon(createColorToolButtonIcon( ":/images/floodfill.png", qVariantValue<QColor>(fillAction->data())));
    fillButtonTriggered();
}

void MainWindow::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
//    lineColorToolButton->setIcon(createColorToolButtonIcon(
//                 ":/images/linecolor.png",
//                 qVariantValue<QColor>(lineAction->data())));
    lineButtonTriggered();
}

void MainWindow::fillButtonTriggered()
{
    //scene->setItemColor(qVariantValue<QColor>(fillAction->data()));
}

void MainWindow::lineButtonTriggered()
{
    //scene->setLineColor(qVariantValue<QColor>(lineAction->data()));
}

void MainWindow::itemSelected(QGraphicsItem *item)
{
    int a=1;
    a++;
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Diagram Scene"),
                       tr("The <b>Diagram Scene</b> example shows "
                          "use of the graphics framework."));
}

void MainWindow::createActions()
{
    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    translateAction = new QAction(QIcon(":/images/translate.png"), tr("Traslate"), this);
    connect(translateAction, SIGNAL(triggered()), this, SLOT(translateItem()));

    rotateAction = new QAction(QIcon(":/images/rotate.png"), tr("Rotate"), this);
    connect(rotateAction, SIGNAL(triggered()), this, SLOT(rotateItem()));

    scaleAction = new QAction(QIcon(":/images/scale.png"), tr("Scale"), this);
    connect(scaleAction, SIGNAL(triggered()), this, SLOT(scaleItem()));

    showCircleAction = new QAction(QIcon(":/images/findCircle.png"), tr("Show Bounding Circle"), this);
    showCircleAction->setCheckable(true);
    connect(showCircleAction, SIGNAL(triggered(bool)), this, SLOT(setBoundingCircle(bool)));

    showControlPointsAction = new QAction(QIcon(":/images/controlPoints.png"), tr("Show Control Points"), this);
    showControlPointsAction->setCheckable(true);
    connect(showControlPointsAction, SIGNAL(triggered(bool)), this, SLOT(showControlPoints(bool)));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);
}

void MainWindow::createToolbars()
{
    // my button group - tools - select, line, curve, rect, polygon

    QToolButton *selectorButton = new QToolButton;
    selectorButton->setCheckable(true);
    selectorButton->setChecked(true);
    selectorButton->setIcon(QIcon(":/images/pointer.png"));

    QToolButton *drawLineButton = new QToolButton;
    drawLineButton->setCheckable(true);
    drawLineButton->setIcon(QIcon(":/images/drawLine.png"));

    QToolButton *drawCurveButton = new QToolButton;
    drawCurveButton->setCheckable(true);
    drawCurveButton->setIcon(QIcon(":/images/drawCurve.png"));

    QToolButton *drawRectButton = new QToolButton;
    drawRectButton->setCheckable(true);
    drawRectButton->setIcon(QIcon(":/images/drawRect.png"));

    QToolButton *drawPolygonButton = new QToolButton;
    drawPolygonButton->setCheckable(true);
    drawPolygonButton->setIcon(QIcon(":/images/drawPolygon.png"));

    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(selectorButton, int(CadScene::Select));
    buttonGroup->addButton(drawLineButton, int(CadScene::InsertLine));
    buttonGroup->addButton(drawCurveButton, int(CadScene::InsertCurve));
    buttonGroup->addButton(drawRectButton, int(CadScene::InsertRect));
    buttonGroup->addButton(drawPolygonButton, int(CadScene::InsertPolygon));
    connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonGroupClicked(int)));

    drawToolbar = addToolBar(tr("Draw"));
    drawToolbar->addWidget(selectorButton);
    drawToolbar->addWidget(drawLineButton);
    drawToolbar->addWidget(drawCurveButton);
    drawToolbar->addWidget(drawRectButton);
    drawToolbar->addWidget(drawPolygonButton);
    //    end of my button group
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(translateAction);
    editToolBar->addAction(rotateAction);
    editToolBar->addAction(scaleAction);
    editToolBar->addAction(showCircleAction);
    editToolBar->addAction(showControlPointsAction);
}

CadItem* MainWindow::castQGraphicsItemToCadItem(QGraphicsItem * item)
{
    switch (item->type())
    {
    case CadLineItem::Type:
        return (qgraphicsitem_cast<CadLineItem *> (item));
        break;
    case CadCurveItem::Type:
        return (qgraphicsitem_cast<CadCurveItem *> (item));
        break;
    case CadRectItem::Type:
        return (qgraphicsitem_cast<CadRectItem *> (item));
        break;
    case CadPolyItem::Type:
        return (qgraphicsitem_cast<CadPolyItem *> (item));
        break;
    default:
        return 0;
    }
}

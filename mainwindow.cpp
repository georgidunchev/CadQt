#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cadscene.h"
#include "cadcontrolpointrectitem.h"
#include <QtGui>
#include <QLabel>
#include <QTransform>

const int InsertTextButton = 10;

MainWindow::MainWindow()
{
    createActions();
    createMenus();

    scene = new CadScene(this);
    scene->setSceneRect(QRectF(0, 0, 1000, 1000));
    connect(scene, SIGNAL(itemInserted()), this, SLOT(itemInserted()));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)), this, SLOT(itemSelected(QGraphicsItem*)));
    connect(scene, SIGNAL(setTracking(bool)), this, SLOT(setTracking(bool)));

    createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("CadQT"));
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::buttonGroupClicked(int id)
{
        scene->setMode(CadScene::Mode(buttonGroup->checkedId()));
}

void MainWindow::deleteItem()
{
    foreach (QGraphicsItem *item, scene->selectedItems()) {
         scene->removeItem(item);
         delete item;
     }
}

void MainWindow::translateItem(bool b)
{
    if (scene->selectedItems().isEmpty())
    {
        translateAction->setChecked(false);
        scene->setTransformationMode(CadScene::None);
        return;
    }
    if(b)
    {
        scene->setTransformationMode(CadScene::Translate);
        scaleAction->setChecked(false);
        rotateAction->setChecked(false);

    }
    else
        scene->setTransformationMode(CadScene::None);
}
void MainWindow::rotateItem(bool b)
{
    if (scene->selectedItems().isEmpty())
    {
        scaleAction->setChecked(false);
        scene->setTransformationMode(CadScene::None);
        return;
    }
    if(b)
    {
        scene->setTransformationMode(CadScene::Rotate);
        scaleAction->setChecked(false);
        translateAction->setChecked(false);
    }
    else
        scene->setTransformationMode(CadScene::None);
}
void MainWindow::scaleItem(bool b)
{
    if (scene->selectedItems().isEmpty())
    {
        scaleAction->setChecked(false);
        scene->setTransformationMode(CadScene::None);
        return;
    }
    if(b)
    {
        scene->setTransformationMode(CadScene::Scale);
        rotateAction->setChecked(false);
        translateAction->setChecked(false);
    }
    else
        scene->setTransformationMode(CadScene::None);
}
void MainWindow::resetOriginPoint()
{
    if (scene->selectedItems().isEmpty())        return;
    CadItem * item = castQGraphicsItemToCadItem(scene->selectedItems().first());
    if(item)
    {
        item->resetOriginPoint();
        scene->update(scene->sceneRect());
    }
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
}

void MainWindow::itemInserted()
{
    buttonGroup->button(int(CadScene::Select))->setChecked(true);
    scene->setMode(CadScene::Select);
    setTracking(false);
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

void MainWindow::itemSelected(QGraphicsItem *item)
{
    int a=1;
    a++;
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About CadQt"),
                       tr("This is a course work for university.\n "
                          "Initially based on the diagram scene tutorial from Qt Creator."));
}

void MainWindow::createActions()
{
    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    translateAction = new QAction(QIcon(":/images/translate.png"), tr("Traslate"), this);
    translateAction->setCheckable(true);
    translateAction->setShortcut(Qt::Key_T);
    connect(translateAction, SIGNAL(triggered(bool)), this, SLOT(translateItem(bool)));

    rotateAction = new QAction(QIcon(":/images/rotate.png"), tr("Rotate"), this);
    rotateAction->setCheckable(true);
    rotateAction->setShortcut(Qt::Key_R);
    connect(rotateAction, SIGNAL(triggered(bool)), this, SLOT(rotateItem(bool)));

    scaleAction = new QAction(QIcon(":/images/scale.png"), tr("Scale"), this);
    scaleAction->setCheckable(true);
    scaleAction->setShortcut(Qt::Key_S);
    connect(scaleAction, SIGNAL(triggered(bool)), this, SLOT(scaleItem(bool)));

    showCircleAction = new QAction(QIcon(":/images/findCircle.png"), tr("Show Bounding Circle"), this);
    showCircleAction->setCheckable(true);
    connect(showCircleAction, SIGNAL(triggered(bool)), this, SLOT(setBoundingCircle(bool)));

    showControlPointsAction = new QAction(QIcon(":/images/controlPoints.png"), tr("Show Control Points"), this);
    showControlPointsAction->setCheckable(true);
    showControlPointsAction->setChecked(true);
    showControlPointsAction->setShortcut(Qt::Key_C);
    connect(showControlPointsAction, SIGNAL(triggered(bool)), this, SLOT(showControlPoints(bool)));

    resetOriginPointAction = new QAction(QIcon(":/images/originPoint.png"), tr("Set Auto Origin Point"), this);
    connect(resetOriginPointAction, SIGNAL(triggered()), this, SLOT(resetOriginPoint()));
    resetOriginPointAction->setShortcut(Qt::Key_O);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);
    fileMenu->addAction(aboutAction);
    actionsMenu = menuBar()->addMenu("Actions");
    actionsMenu->addAction(translateAction);
    actionsMenu->addAction(rotateAction);
    actionsMenu->addAction(scaleAction);
    actionsMenu->addAction(showCircleAction);
    actionsMenu->addAction(showControlPointsAction);
    actionsMenu->addAction(resetOriginPointAction);
}

void MainWindow::createToolbars()
{
    // my button group - tools - select, line, curve, rect, polygon

    QToolButton *selectorButton = new QToolButton;
    selectorButton->setCheckable(true);
    selectorButton->setChecked(true);
    selectorButton->setShortcut(Qt::Key_Escape);
    selectorButton->setIcon(QIcon(":/images/pointer.png"));

    QToolButton *drawLineButton = new QToolButton;
    drawLineButton->setCheckable(true);
    drawLineButton->setShortcut(Qt::Key_F1);
    drawLineButton->setIcon(QIcon(":/images/drawLine.png"));

    QToolButton *drawCurveButton = new QToolButton;
    drawCurveButton->setCheckable(true);
    drawCurveButton->setShortcut(Qt::Key_F2);
    drawCurveButton->setIcon(QIcon(":/images/drawCurve.png"));

    QToolButton *drawRectButton = new QToolButton;
    drawRectButton->setCheckable(true);
    drawRectButton->setShortcut(Qt::Key_F3);
    drawRectButton->setIcon(QIcon(":/images/drawRect.png"));

    QToolButton *drawPolygonButton = new QToolButton;
    drawPolygonButton->setCheckable(true);
    drawPolygonButton->setShortcut(Qt::Key_F4);
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
    editToolBar->addAction(resetOriginPointAction);
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

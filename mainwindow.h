#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "caditem.h"

class CadScene;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE

//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();

//public slots:
   CadItem* castQGraphicsItemToCadItem(QGraphicsItem * item);

private slots:
    void backgroundButtonGroupClicked(QAbstractButton *button);
    void buttonGroupClicked(int id);
    void deleteItem();
    void pointerGroupClicked(int id);

    void translateItem();
    void rotateItem();
    void scaleItem();

    void showControlPoints(bool b);
    void setBoundingCircle(bool b);
    void resetOriginPoint();

    void setTracking(bool b);

    void itemInserted();

    void sceneScaleChanged(const QString &scale);

    void itemColorChanged();
    void lineColorChanged();

    void fillButtonTriggered();
    void lineButtonTriggered();

    void itemSelected(QGraphicsItem *item);
    void about();
//    CadItem* castQGraphicsItemToCadItem(QGraphicsItem * item);

private:
    void createActions();
    void createMenus();
    void createToolbars();
//    QMenu *createColorMenu(const char *slot, QColor defaultColor);
//    QIcon createColorToolButtonIcon(const QString &image, QColor color);
//    QIcon createColorIcon(QColor color);

    CadScene *scene;
    QGraphicsView *view;

    QAction *exitAction;
    QAction *addAction;
    QAction *deleteAction;

    QAction *translateAction;
    QAction *rotateAction;
    QAction *scaleAction;

    QAction *showCircleAction;
    QAction *showControlPointsAction;
    QAction *resetOriginPointAction;

    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *shapeMenu;
    QMenu * actionsMenu;
    QMenu *aboutMenu;

    QToolBar *textToolBar;
    QToolBar *editToolBar;
    QToolBar *colorToolBar;
    QToolBar *pointerToolbar;
    QToolBar *drawToolbar;


    QComboBox *sceneScaleCombo;
    QComboBox *itemColorCombo;
    QComboBox *textColorCombo;
    QComboBox *fontSizeCombo;
    QFontComboBox *fontCombo;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;
//    QButtonGroup *buttonGroup;
    QToolButton *fontColorToolButton;
    QToolButton *fillColorToolButton;
    QToolButton *lineColorToolButton;
    QAction *boldAction;
    QAction *underlineAction;
    QAction *italicAction;
    QAction *textAction;
    QAction *fillAction;
    QAction *lineAction;
};

#endif

#ifndef CADSCENE_H
#define CADSCENE_H

#include <QGraphicsScene>
//#include <QWidget>
#include "caditem.h"
#include "cadlineitem.h"
#include "cadcurveitem.h"
#include "cadrectitem.h"
#include "cadpolyitem.h"
#include "cadboundingcircle.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

class CadScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { Select, Drawing, InsertLine, InsertCurve, InsertRect, InsertPolygon, MoveItem };

    CadScene(/*QMenu *itemMenu,*/ QObject *parent = 0);

    QFont font() const
        { return myFont; }
    QColor textColor() const
        { return myTextColor; }
    QColor itemColor() const
        { return myItemColor; }
    QColor lineColor() const
        { return myLineColor; }
    void setLineColor(const QColor &color);
//    void setTextColor(const QColor &color);
    void setItemColor(const QColor &color);
//    void setFont(const QFont &font);
    void setBoundingCircle(bool b);
    bool isBoundingCircleOn();
//    void setBoundingCircle(CadItem *item);
    void setControlPoints(bool b);
    bool isControlPointsOn();



public slots:
    void setMode(Mode mode);
    void setItemType(CadItem::CadType type);
//    void editorLostFocus(DiagramTextItem *item);

signals:
    void itemInserted();
//    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);
    void setTracking(bool b);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    bool isItemChange(int type);

    bool bBoundingCircle;
    bool bControlPoints;
//    CadBoundingCircle * boundingCircle;

    CadItem::CadType myItemType;
    QMenu *myItemMenu;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    CadLineItem *line;
    CadItem *tempItem;
    QFont myFont;
//    DiagramTextItem *textItem;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;
};
#endif // CADSCENE_H

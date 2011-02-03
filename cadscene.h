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
    enum Mode { Select, Drawing, InsertLine, InsertCurve, InsertRect, InsertPolygon,/* MoveItem,*/};
    enum transformationMode { None, Translate, Rotate, Scale };

    CadScene(QObject *parent = 0);

    void setBoundingCircle(bool b);
    bool isBoundingCircleOn();
    void setControlPoints(bool b);
    bool isControlPointsOn();
    int getMode();
    void setTransformationMode(transformationMode mode);
    uint getTransMode();

public slots:
    void setMode(Mode mode);
    void setItemType(CadItem::CadType type);

signals:
    void itemInserted();
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
    bool bAutoOriginPoint;

    CadItem::CadType myItemType;
    QMenu *myItemMenu;
    Mode myMode;
    transformationMode myTransMode;
    bool leftButtonDown;
    QPointF startPoint;
    CadLineItem *line;
    CadItem *tempItem;
};
#endif // CADSCENE_H

#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H

#include "caditem.h"
#include <QGraphicsItem>
#include "cadlineitem.h"
#include "cadrectitem.h"
#include "cadpolyitem.h"

class GlobalFunctions
{
public:
    GlobalFunctions();
    CadItem* castQGraphicsItemToCadItem(QGraphicsItem * item);
};

#endif // GLOBALFUNCTIONS_H

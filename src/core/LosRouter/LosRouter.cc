#include "core/LosRouter/LosRouter.h"

namespace LosCore
{

LosRouter &LosRouter::instance()
{
    static LosRouter router;
    return router;
}

LosRouter::LosRouter(QObject *parent)
    : QObject(parent)
{
}

}

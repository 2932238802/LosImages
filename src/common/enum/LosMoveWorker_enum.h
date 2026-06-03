#pragma once

#include <QMetaType>

namespace LosCommon
{

struct LosMoveSummary
{
    int L_found = 0;
    int L_moved = 0;
    int L_renamed = 0;
    int L_skipped = 0;
    int L_failed = 0;
};

}

Q_DECLARE_METATYPE(LosCommon::LosMoveSummary)

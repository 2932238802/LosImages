#pragma once

#include <QStringList>

namespace LosCommon
{
namespace LosMoveWorker_str
{
inline QStringList ImagePatterns()
{
    return {
        QStringLiteral("*.bmp"),
        QStringLiteral("*.dib"),
        QStringLiteral("*.jpg"),
        QStringLiteral("*.jpeg"),
        QStringLiteral("*.png"),
        QStringLiteral("*.gif"),
        QStringLiteral("*.webp"),
        QStringLiteral("*.tif"),
        QStringLiteral("*.tiff")
    };
}
}
}

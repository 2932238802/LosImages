#pragma once

#include <QObject>

#include "common/enum/LosMoveWorker_enum.h"

namespace LosCore
{

class LosRouter : public QObject
{
    Q_OBJECT

public:
    static LosRouter &instance();

signals:
    void _ls_progressRangeChanged(int minimum, int maximum);
    void _ls_progressValueChanged(int value);
    void _ls_logMessage(const QString &message);
    void _ls_moveFinished(const LosCommon::LosMoveSummary &summary);

private:
    explicit LosRouter(QObject *parent = nullptr);
};

}

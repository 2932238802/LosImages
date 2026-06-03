#pragma once

#include <QMainWindow>
#include <functional>
#include "common/enum/LosMoveWorker_enum.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LosMainWindow;
}
QT_END_NAMESPACE

namespace LosView {

class LosMainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit LosMainWindow(QWidget *parent = nullptr);
    ~LosMainWindow() override;

  private slots: // chs
    void addSourceFolders();
    void removeSelectedSourceFolder();
    void clearSourceFolders();
    void browseTargetFolder();
    void scanImages();
    void startMove();
    void onMoveFinished(const LosCommon::LosMoveSummary &summary);
    void appendLog(const QString &message);


  private: // init
    void initConnection();
    QStringList sourceDirectories() const;
    int countImagesInSources() const;

  private: // tool
    void setBusy(bool busy);
    bool validateInputs() const;
    void openDirectoryDialog(const QString &title, const std::function<void(const QString &)> &handler);

  private: // param
    Ui::LosMainWindow *LOS_ui = nullptr;
    QThread *L_workerThread = nullptr;
};

} // namespace LosView

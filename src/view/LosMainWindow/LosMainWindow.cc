#include "ui_LosMainWindow.h"

#include "common/num/LosMainWindow_num.h"
#include "common/str/LosMoveWorker_str.h"
#include "common/util/LosPathUtil/LosPathUtil.h"
#include "core/LosMoveWorker/LosMoveWorker.h"
#include "core/LosRouter/LosRouter.h"
#include "view/LosMainWindow/LosMainWindow.h"
#include "view/style/LosMainWindow_style.h"
#include <QDateTime>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QSplitter>
#include <QThread>

namespace LosView {

LosMainWindow::LosMainWindow(QWidget *parent) : QMainWindow(parent), LOS_ui(new Ui::LosMainWindow) {
    qRegisterMetaType<LosCommon::LosMoveSummary>("LosCommon::LosMoveSummary");
    LOS_ui->setupUi(this);
    resize(LosCommon::LosMainWindow_num::DEFAULT_WIDTH, LosCommon::LosMainWindow_num::DEFAULT_HEIGHT);
    LOS_ui->mainSplitter->setStretchFactor(0, 4);
    LOS_ui->mainSplitter->setStretchFactor(1, 1);
    LOS_ui->mainSplitter->setSizes({520, 180});
    setStyleSheet(QString::fromStdString(LosMainWindow_style::getStyle()));
    initConnection();

    appendLog(QStringLiteral("程序已启动 请添加源文件夹并选择目标文件夹"));
}

LosMainWindow::~LosMainWindow() {
    if (L_workerThread != nullptr) {
        L_workerThread->quit();
        L_workerThread->wait();
    }

    delete LOS_ui;
}

void LosMainWindow::initConnection() {
    connect(LOS_ui->addSourceButton, &QPushButton::clicked, this, &LosMainWindow::addSourceFolders);
    connect(LOS_ui->removeSourceButton, &QPushButton::clicked, this, &LosMainWindow::removeSelectedSourceFolder);
    connect(LOS_ui->clearSourceButton, &QPushButton::clicked, this, &LosMainWindow::clearSourceFolders);
    connect(LOS_ui->browseTargetButton, &QPushButton::clicked, this, &LosMainWindow::browseTargetFolder);
    connect(LOS_ui->scanButton, &QPushButton::clicked, this, &LosMainWindow::scanImages);
    connect(LOS_ui->startButton, &QPushButton::clicked, this, &LosMainWindow::startMove);
    connect(&LosCore::LosRouter::instance(), &LosCore::LosRouter::_ls_progressRangeChanged, LOS_ui->progressBar, &QProgressBar::setRange);
    connect(&LosCore::LosRouter::instance(), &LosCore::LosRouter::_ls_progressValueChanged, LOS_ui->progressBar, &QProgressBar::setValue);
    connect(&LosCore::LosRouter::instance(), &LosCore::LosRouter::_ls_logMessage, this, &LosMainWindow::appendLog);
    connect(&LosCore::LosRouter::instance(), &LosCore::LosRouter::_ls_moveFinished, this, &LosMainWindow::onMoveFinished);
}


/**
 * @brief
 *
 * @param message
 */
void LosMainWindow::appendLog(const QString &message) {
    const QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss"));
    LOS_ui->logEdit->append(QStringLiteral("[%1] %2").arg(timestamp, message));
}



/**
 * @brief
 *
 * @return QStringList
 */
QStringList LosMainWindow::sourceDirectories() const {
    QStringList dirs;
    for (int row = 0; row < LOS_ui->sourceList->count(); ++row) {
        dirs.append(LOS_ui->sourceList->item(row)->text());
    }
    return dirs;
}



/**
 * @brief
 *
 * @return true
 * @return false
 */
bool LosMainWindow::validateInputs() const {
    if (LOS_ui->sourceList->count() == 0) {
        QMessageBox::warning(const_cast<LosMainWindow *>(this), QStringLiteral("提示"), QStringLiteral("请至少添加一个源文件夹 "));
        return false;
    }
    if (LOS_ui->targetEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(const_cast<LosMainWindow *>(this), QStringLiteral("提示"), QStringLiteral("请选择目标文件夹 "));
        return false;
    }
    const QString target_dir = LosCommon::LosPathUtil::NormalizePath(LOS_ui->targetEdit->text().trimmed());
    for (const QString &source_dir : sourceDirectories()) {
        if (LosCommon::LosPathUtil::NormalizePath(source_dir).compare(target_dir, Qt::CaseInsensitive) == 0) {
            QMessageBox::warning(const_cast<LosMainWindow *>(this), QStringLiteral("提示"), QStringLiteral("源文件夹和目标文件夹不能相同 "));
            return false;
        }
    }
    return true;
}



/**
 * @brief
 *
 * @return int
 */
int LosMainWindow::countImagesInSources() const {
    const QStringList patterns = LosCommon::LosMoveWorker_str::ImagePatterns();
    const QString target_dir =
        LOS_ui->targetEdit->text().trimmed().isEmpty() ? QString() : LosCommon::LosPathUtil::NormalizePath(LOS_ui->targetEdit->text().trimmed());
    int count = 0;
    // IteratorFlags 要不要递归了
    const QDirIterator::IteratorFlags flags = LOS_ui->recursiveCheck->isChecked() ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;
    for (const QString &source_dir : sourceDirectories()) {
        QDirIterator it(source_dir, patterns, QDir::Files, flags);
        while (it.hasNext()) {
            const QString file_path = LosCommon::LosPathUtil::NormalizePath(it.next());
            if (!target_dir.isEmpty() && LosCommon::LosPathUtil::IsSameOrChildPath(file_path, target_dir)) {
                continue;
            }
            ++count;
        }
    }
    return count;
}



/**
 * @brief
 *
 * @param busy
 */
void LosMainWindow::setBusy(bool busy) {
    LOS_ui->scanButton->setEnabled(!busy);
    LOS_ui->startButton->setEnabled(!busy);
    LOS_ui->recursiveCheck->setEnabled(!busy);
    LOS_ui->addSourceButton->setEnabled(!busy);
    LOS_ui->removeSourceButton->setEnabled(!busy);
    LOS_ui->clearSourceButton->setEnabled(!busy);
    LOS_ui->browseTargetButton->setEnabled(!busy);
    LOS_ui->sourceList->setEnabled(!busy);
    LOS_ui->targetEdit->setEnabled(!busy);
}



/**
 * @brief
 *
 * @param title
 * @param handler
 */
void LosMainWindow::openDirectoryDialog(const QString &title, const std::function<void(const QString &)> &handler) {
    QFileDialog dialog(this, title);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.setStyleSheet(QString::fromStdString(LosMainWindow_style::GetDirectoryDialogStyle()));
    if (dialog.exec() != QDialog::Accepted) {
        return;
    }
    const QStringList selected_dirs = dialog.selectedFiles();
    if (selected_dirs.isEmpty()) {
        return;
    }
    handler(selected_dirs.first());
}



/**
 * @brief addSourceFolders
 *
 */
void LosMainWindow::addSourceFolders() {
    openDirectoryDialog(QStringLiteral("选择源文件夹"), [this](const QString &dir) {
        const QString normalized = LosCommon::LosPathUtil::NormalizePath(dir);
        for (int row = 0; row < LOS_ui->sourceList->count(); ++row) {
            if (LosCommon::LosPathUtil::NormalizePath(LOS_ui->sourceList->item(row)->text()).compare(normalized, Qt::CaseInsensitive) == 0) {
                appendLog(QStringLiteral("忽略重复源文件夹 %1").arg(normalized));
                return;
            }
        }
        LOS_ui->sourceList->addItem(normalized);
        appendLog(QStringLiteral("已添加源文件夹 %1").arg(normalized));
    });
}



/**
 * @brief
 *
 */
void LosMainWindow::removeSelectedSourceFolder() {
    const int current_row = LOS_ui->sourceList->currentRow();
    if (current_row < 0) {
        return;
    }
    const QString removed_path = LOS_ui->sourceList->item(current_row)->text();
    delete LOS_ui->sourceList->takeItem(current_row);
    appendLog(QStringLiteral("已移除源文件夹 %1").arg(removed_path));
}



/**
 * @brief
 *
 */
void LosMainWindow::clearSourceFolders() {
    LOS_ui->sourceList->clear();
    appendLog(QStringLiteral("源文件夹列表已清空 "));
}



/**
 * @brief
 *
 */
void LosMainWindow::browseTargetFolder() {
    openDirectoryDialog(QStringLiteral("选择目标文件夹"), [this](const QString &dir) {
        LOS_ui->targetEdit->setText(LosCommon::LosPathUtil::NormalizePath(dir));
        appendLog(QStringLiteral("目标文件夹 %1").arg(LosCommon::LosPathUtil::NormalizePath(dir)));
    });
}



/**
 * @brief scanImages
 *
 */
void LosMainWindow::scanImages() {
    if (!validateInputs()) {
        return;
    }
    const int count = countImagesInSources();
    // summaryLabel 就是等待扫描的 Label
    LOS_ui->summaryLabel->setText(QStringLiteral("共扫描到 %1 张图片 ").arg(count));
    appendLog(QStringLiteral("扫描完成 当前条件下共有 %1 张图片待处理 ").arg(count));
}



/**
 * @brief startMove
 *
 */
void LosMainWindow::startMove() {
    if (!validateInputs()) {
        return;
    }
    const QString target_dir = LosCommon::LosPathUtil::NormalizePath(LOS_ui->targetEdit->text().trimmed());
    QDir dir;
    if (!dir.exists(target_dir) && !dir.mkpath(target_dir)) {
        QMessageBox::critical(this, QStringLiteral("错误"), QStringLiteral("无法创建目标文件夹"));
        return;
    }
    if (L_workerThread != nullptr) {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("任务正在执行中 请稍候 "));
        return;
    }
    appendLog(QStringLiteral("开始转移图片到 %1").arg(target_dir));
    LOS_ui->progressBar->setRange(LosCommon::LosMainWindow_num::DEFAULT_PROGRESS_MINIMUM, LosCommon::LosMainWindow_num::DEFAULT_PROGRESS_MAXIMUM);
    LOS_ui->progressBar->setValue(LosCommon::LosMainWindow_num::DEFAULT_PROGRESS_MINIMUM);
    setBusy(true);
    L_workerThread = new QThread(this);
    auto *worker = new LosCore::LosMoveWorker(sourceDirectories(), target_dir, LOS_ui->recursiveCheck->isChecked());
    worker->moveToThread(L_workerThread);
    connect(L_workerThread, &QThread::started, worker, &LosCore::LosMoveWorker::process);
    connect(&LosCore::LosRouter::instance(), &LosCore::LosRouter::_ls_moveFinished, L_workerThread, &QThread::quit);
    connect(L_workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(L_workerThread, &QThread::finished, L_workerThread, &QObject::deleteLater);
    connect(L_workerThread, &QThread::finished, this, [this]() {
        L_workerThread = nullptr;
        setBusy(false);
    });
    L_workerThread->start();
}



/**
 * @brief
 *
 * @param summary
 */
void LosMainWindow::onMoveFinished(const LosCommon::LosMoveSummary &summary) {
    LOS_ui->summaryLabel->setText(QStringLiteral("发现 %1 成功 %2 重命名 %3 跳过 %4 失败 %5")
                                      .arg(summary.L_found)
                                      .arg(summary.L_moved)
                                      .arg(summary.L_renamed)
                                      .arg(summary.L_skipped)
                                      .arg(summary.L_failed));
    appendLog(QStringLiteral("任务结束 发现 %1 成功 %2 重命名 %3 跳过 %4 失败 %5 ")
                  .arg(summary.L_found)
                  .arg(summary.L_moved)
                  .arg(summary.L_renamed)
                  .arg(summary.L_skipped)
                  .arg(summary.L_failed));
    QMessageBox::information(this, QStringLiteral("完成"),
                             QStringLiteral("处理完成 -> \n发现 %1\n成功 %2\n重命名 %3\n跳过 %4\n失败 %5")
                                 .arg(summary.L_found)
                                 .arg(summary.L_moved)
                                 .arg(summary.L_renamed)
                                 .arg(summary.L_skipped)
                                 .arg(summary.L_failed));
}

} // namespace LosView

#include "core/LosMoveWorker/LosMoveWorker.h"

#include "common/enum/LosMoveWorker_enum.h"
#include "common/str/LosMoveWorker_str.h"
#include "common/util/LosPathUtil/LosPathUtil.h"
#include "core/LosRouter/LosRouter.h"

#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>

#include <utility>

namespace LosCore {

/**
 * @brief Construct a new Los Move Worker:: Los Move Worker object
 *
 * @param source_dirs
 * @param target_dir
 * @param recursive
 * @param parent
 */
LosMoveWorker::LosMoveWorker(QStringList source_dirs, QString target_dir, bool recursive, QObject *parent)
    : QObject(parent), L_sourceDirs(std::move(source_dirs)), L_targetDir(LosCommon::LosPathUtil::NormalizePath(target_dir)), L_recursive(recursive),
      L_patterns(LosCommon::LosMoveWorker_str::ImagePatterns()) {
    const QDir target_dir_info(L_targetDir);
    const QFileInfoList existing_files = target_dir_info.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    for (const QFileInfo &file_info : existing_files) {
        L_reservedNames.insert(file_info.fileName().toLower());
    }
}



/**
 * @brief
 *
 * @return QStringList
 */
QStringList LosMoveWorker::collectImageFiles() const {
    QStringList files;
    const QDirIterator::IteratorFlags flags = L_recursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;
    for (const QString &source_dir : L_sourceDirs) {
        QDirIterator it(source_dir, L_patterns, QDir::Files, flags);
        while (it.hasNext()) {
            const QString file_path = LosCommon::LosPathUtil::NormalizePath(it.next());
            if (LosCommon::LosPathUtil::IsSameOrChildPath(file_path, L_targetDir)) {
                continue;
            }
            files.append(file_path);
        }
    }
    return files;
}



/**
 * @brief
 *
 * @param source_file_path
 * @return QString
 */
QString LosMoveWorker::buildUniqueTargetPath(const QString &source_file_path) {
    const QFileInfo source_info(source_file_path);
    const QString suffix = source_info.suffix();
    const QString dot_suffix = suffix.isEmpty() ? QString() : QStringLiteral(".") + suffix;
    const QString base_name = source_info.completeBaseName();

    QString candidate_name = source_info.fileName();
    int counter = 1;

    while (L_reservedNames.contains(candidate_name.toLower())) {
        candidate_name = QStringLiteral("%1_%2%3").arg(base_name).arg(counter).arg(dot_suffix);
        ++counter;
    }

    L_reservedNames.insert(candidate_name.toLower());
    return QDir(L_targetDir).filePath(candidate_name);
}



/**
 * @brief
 *
 * @param source_file_path
 * @param target_file_path
 * @param error_message
 * @return true
 * @return false
 */
bool LosMoveWorker::moveFile(const QString &source_file_path, const QString &target_file_path, QString *error_message) {
    QFile file(source_file_path);
    if (file.rename(target_file_path)) {
        return true;
    }
    const QString rename_error = file.errorString();
    if (!file.copy(target_file_path)) {
        if (error_message != nullptr) {
            *error_message = QStringLiteral("直接重命名失败 %1 复制失败 %2").arg(rename_error, file.errorString());
        }
        return false;
    }
    if (!file.remove()) {
        QFile::remove(target_file_path);
        if (error_message != nullptr) {
            *error_message = QStringLiteral("复制成功 但删除源文件失败 %1").arg(file.errorString());
        }
        return false;
    }
    return true;
}



/**
 * @brief process
 *
 */
void LosMoveWorker::process() {
    LosCommon::LosMoveSummary summary;
    const QStringList files = collectImageFiles();
    summary.L_found = files.size();
    emit LosRouter::instance()._ls_logMessage(QStringLiteral("扫描完成 共发现 %1 张图片 ").arg(summary.L_found));
    emit LosRouter::instance()._ls_progressRangeChanged(0, summary.L_found);
    for (int index = 0; index < files.size(); ++index) {
        const QString &source_file = files.at(index);
        const QString target_file = buildUniqueTargetPath(source_file);
        const QFileInfo source_info(source_file);
        const QFileInfo target_info(target_file);

        if (LosCommon::LosPathUtil::NormalizePath(source_info.absolutePath())
                    .compare(LosCommon::LosPathUtil::NormalizePath(L_targetDir), Qt::CaseInsensitive) == 0 &&
            source_info.fileName().compare(target_info.fileName(), Qt::CaseInsensitive) == 0) {
            ++summary.L_skipped;
            emit LosRouter::instance()._ls_logMessage(QStringLiteral("跳过 %1 已经位于目标文件夹 ").arg(source_info.fileName()));
            emit LosRouter::instance()._ls_progressValueChanged(index + 1);
            continue;
        }

        QString error_message;
        if (moveFile(source_file, target_file, &error_message)) {
            ++summary.L_moved;
            if (source_info.fileName().compare(target_info.fileName(), Qt::CaseInsensitive) != 0) {
                ++summary.L_renamed;
                emit LosRouter::instance()._ls_logMessage(
                    QStringLiteral("已移动并重命名 %1 -> %2").arg(source_info.fileName(), target_info.fileName()));
            } else {
                emit LosRouter::instance()._ls_logMessage(QStringLiteral("已移动 %1").arg(source_info.fileName()));
            }
        } else {
            ++summary.L_failed;
            emit LosRouter::instance()._ls_logMessage(QStringLiteral("失败 %1 原因 %2").arg(source_info.fileName(), error_message));
        }
        emit LosRouter::instance()._ls_progressValueChanged(index + 1);
    }
    emit LosRouter::instance()._ls_moveFinished(summary);
}

} // namespace LosCore

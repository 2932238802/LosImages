#pragma once

#include "common/util/LosPathUtil/LosPathUtil.h"
#include <QDir>
#include <QString>
namespace LosCommon {
namespace LosPathUtil {

/**
 * @brief
 *
 * @param path
 * @return QString
 */
inline QString NormalizePath(const QString &path) { return QDir::cleanPath(QDir(path).absolutePath()); }



/**
 * @brief
 *
 * @param candidate_path
 * @param parent_path
 * @return true
 * @return false
 */
inline bool IsSameOrChildPath(const QString &candidate_path, const QString &parent_path) {
    const QString normalized_candidate = NormalizePath(candidate_path);
    const QString normalized_parent = NormalizePath(parent_path);
    if (normalized_candidate.compare(normalized_parent, Qt::CaseInsensitive) == 0) {
        return true;
    }
    const QString prefix = normalized_parent + QDir::separator();
    return normalized_candidate.startsWith(prefix, Qt::CaseInsensitive);
}

} // namespace LosPathUtil
} // namespace LosCommon

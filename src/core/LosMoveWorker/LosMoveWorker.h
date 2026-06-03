#pragma once

#include <QObject>
#include <QSet>
#include <QStringList>

namespace LosCore
{

class LosMoveWorker : public QObject
{
    Q_OBJECT

public:
    explicit LosMoveWorker(QStringList source_dirs, QString target_dir, bool recursive, QObject *parent = nullptr);

public slots:
    void process();

private:
    QStringList collectImageFiles() const;
    QString buildUniqueTargetPath(const QString &source_file_path);
    bool moveFile(const QString &source_file_path, const QString &target_file_path, QString *error_message);

    QStringList L_sourceDirs;
    QString L_targetDir;
    bool L_recursive = true;
    QStringList L_patterns;
    QSet<QString> L_reservedNames;
};

}

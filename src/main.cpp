#include <QApplication>

#include "view/LosMainWindow/LosMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName(QStringLiteral("批量转移图片工具"));
    QApplication::setOrganizationName(QStringLiteral("QtDemoCollection"));
    LosView::LosMainWindow window;
    window.show();
    return app.exec();
}

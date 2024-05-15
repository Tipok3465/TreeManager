#include "App.h"
#include "header.h"
#include "fstream"

int32_t main(int32_t argc, char *argv[])
{
    QApplication a(argc, argv);
    App TreeManager(1000, 600);
    TreeManager.render();
    return QApplication::exec();
}

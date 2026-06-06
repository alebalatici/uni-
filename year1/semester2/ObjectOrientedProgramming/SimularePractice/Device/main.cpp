#include "tests/tests.h"
#include <QApplication>

#include "gui/gui.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Tests::test_all();

    RepoDeviceFile repo("data/device.txt");
    ServiceDevice srv{repo};

    GraphicalInterface gui{srv};
    gui.show();
    return app.exec();
}

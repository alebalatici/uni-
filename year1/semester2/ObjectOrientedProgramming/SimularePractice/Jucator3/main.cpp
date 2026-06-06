#include "tests/tests.h"
#include "gui/gui.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Tests::test_all();

    RepoJucatorFile repo{"data/jucatori.txt"};
    ServiceJucator srv{repo};
    GraphicalInterface gui{srv};

    gui.show();
    return app.exec();
}

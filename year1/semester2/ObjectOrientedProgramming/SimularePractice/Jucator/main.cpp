#include <QApplication>

#include "gui/gui.h"
#include "tests/tests.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Tests::test_all();

    RepoJucatoriFile repo{"data/jucatori.txt"};
    ServiceJucatori srv{repo};
    GraphicalInterface gui{srv};
    gui.show();
    return app.exec();
}
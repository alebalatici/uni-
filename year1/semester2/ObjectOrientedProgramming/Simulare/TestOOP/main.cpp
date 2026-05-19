#include <iostream>
#include "tests/tests.h"
#include "gui/gui.h"
#include <QApplication>
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Tests::test_all();

    RepoRadiationFile repo("data/radiatii.txt");
    Validator val;
    ServiceRadiation srv{repo, val};

    GraphicalInterface gui{srv};

    gui.show();
    return QApplication::exec();
  //  return 0;
}
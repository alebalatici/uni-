#include "tests/tests_domain.h"
#include "tests/tests_repo.h"
#include "tests/tests_service.h"
#include <QApplication>
#include <qt6/QtWidgets/qapplication.h>
#include "gui/gui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TestsDomain::test_all_domain();
    TestsRepo::test_all_repo();
    TestsService::test_all_service();

    RepoMelodiiFile repo{"data/melodii.txt"};
    Validator val;
    ServiceMelodii srv{repo, val};

    GraphicalInterface gui{srv};
    gui.show();
    return QApplication::exec();
}

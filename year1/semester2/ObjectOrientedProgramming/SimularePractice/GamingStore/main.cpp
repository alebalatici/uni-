#include <QApplication>
#include "tests/tests_repo.h"
#include "tests/tests_service.h"
#include "gui/gui.h"
#include "service/service_joc.h"
int main(int argc, char *argv[])
{
    QApplication app{argc, argv};
    TestsRepo::test_all_repo();
    TestsService::test_all_srv();

    RepoJocFile repo("data/jocuri.txt");
    ServiceJoc srv{repo};

    GraphicalInterface gui{srv};
    gui.show();
    return app.exec();
}

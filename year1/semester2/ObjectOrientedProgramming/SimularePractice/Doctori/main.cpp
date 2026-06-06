#include <QApplication>
#include "tests/tests_repo.h"
#include "tests/tests_service.h"
#include "repo/repo_doctor.h"
#include "service/service_doctor.h"
#include "gui/gui.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TestsRepo::test_all();
    TestsService::test_all();

    RepoDoctorFile repo("data/doctori.txt");
    ServiceDoctor srv{repo};

    GraphicalInterface gui{srv};
    gui.show();
    return app.exec();
}

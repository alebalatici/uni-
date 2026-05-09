#include <iostream>
#include <stdexcept>
#include <QApplication>
#include "tests/tests_domain.h"
#include "tests/tests_repo.h"
#include "tests/tests_service.h"
#include "tests/tests_lista_notificare.h"
#include "ui/ui.h"
#include "gui/gui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TestsDomain::test_all_domain();
    TestsRepo::test_all_repo();
    TestsService::test_all_service();
    TestsListaNotificare::test_all_lista_notificare();

    RepoLocatariFile repo("data/locatari.txt");
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    //Console console{srv};
    //console.run();

    GraphicalInterface gui{srv};
    gui.show();
    return app.exec();
}
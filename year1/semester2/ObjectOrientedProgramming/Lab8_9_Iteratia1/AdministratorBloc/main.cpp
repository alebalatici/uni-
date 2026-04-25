#include <iostream>
#include "tests/tests_domain.h"
#include "tests/tests_repo.h"
#include "tests/tests_service.h"
#include "tests/tests_lista_notificare.h"
#include "ui/ui.h"

int main() {
    TestsDomain::test_all_domain();
    TestsRepo::test_all_repo();
    TestsService::test_all_service();
    TestsListaNotificare::test_all_lista_notificare();

    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};
    Console console{srv};
    console.run();
    vector<Locatar> locatari;
    return 0;
}
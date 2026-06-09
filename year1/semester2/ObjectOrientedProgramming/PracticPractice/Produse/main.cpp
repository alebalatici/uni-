#include "tests/tests_domain.h"
#include "tests/tests_repo.h"
#include "tests/tests_service.h"
#include "gui/gui.h"
#include "gui/type_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TestsDomain::test_all_domain();
    TestsRepo::test_all_repo();
    TestsService::test_all_service();

    RepoProdusFile repo("data/produse.txt");
    Validator val;
    ServiceProdus srv{repo, val};

    for (const auto& pair : ServiceProdus::get_count_type(srv.get_all_produse()))
    {
        TypeWindow* window = new TypeWindow(srv, pair.first);
        window->setWindowTitle(QString::fromStdString(pair.first));
        window->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        window->setMinimumHeight(250);
        window->setMinimumWidth(250);
        window->show();
    }

    GraphicalInterface gui{srv};
    gui.show();

    return QApplication::exec();
}

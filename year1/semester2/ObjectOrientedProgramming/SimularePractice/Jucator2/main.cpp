#include <QApplication>
#include "gui/gui.h"
#include "tests/tests.h"

int main(int argc,  char *argv[])
{
    try
    {
         QApplication app(argc, argv);

    Tests::test_all();

    RepoJucatoriFile repo{"data/jucatori.txt"};
    ServiceJucatori srv{repo};

    GraphicalInterface gui{srv};
    gui.show();
    return app.exec();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (const std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
    }
}

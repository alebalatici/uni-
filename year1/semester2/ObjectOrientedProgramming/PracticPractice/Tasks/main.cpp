#include "tests/tests.h"
#include <QApplication>
#include "gui/gui.h"
#include "gui/task_window.h"
int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Tests::testAll();
    RepoTasksFile repo{"data/tasks.txt"};
    Validator val;
    ServiceTasks srv{repo, val};
    GraphicalInterface gui{srv};
    gui.show();

    vector<string> title{"open", "inprogress", "closed"};
    for (int i = 0; i < 3; i++)
    {
        TaskWindow* task_window = new TaskWindow(srv, title[i]);
        task_window->setWindowTitle(QString::fromStdString(title[i]));
        task_window->show();
    }

    return QApplication::exec();
}

//
// Created by Alexandra on 6/9/2026.
//

#ifndef TASKS_TESTS_H
#define TASKS_TESTS_H
#include <string>
#include <cassert>

#include "../repository/repo_tasks.h"
#include "../service/srv_tasks.h"
class Tests {
    private:
    static void copyTargetTemplate(const string& targetFilename, const string& templateFilename)
    {
        ifstream fin{templateFilename};
        ofstream fout{targetFilename};
        if (!fin.is_open())
        {
            throw std::runtime_error("Could not open file " + templateFilename);
        }
        if (!fout.is_open())
        {
            throw std::runtime_error("Could not open file " + targetFilename);
        }
        fout << fin.rdbuf();
        fin.close();
        fout.close();
    }

    static void testValidate()
    {
        Validator val;
        Task t1{11,"descriere11", vector<string>{"Nume1","Nume2"}, "inprogress"};
        try
        {
            val.validate(t1);
            assert(true);
        }
        catch (std::exception&)
        {
            assert(false);
        }
        Task t2{11,"", vector<string>{"Nume1","Nume2"}, "inprogress"};
        try
        {
            val.validate(t2);
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
        Task t3{11,"", vector<string>{"Nume1","Nume2"}, "abc"};
        try
        {
            val.validate(t3);
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
        Task t4{11,"", vector<string>{"Nume1","Nume2","Nume3","Nume4","Nume5"}, "inprogress"};
        try
        {
            val.validate(t4);
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
    }

    static void testAddRepo()
    {
        copyTargetTemplate("data/test_tasks.txt", "data/default_tasks.txt");
        RepoTasksFile repo("data/test_tasks.txt");
        assert(repo.getTasks().size() == 10);
        assert(repo.getTasks()[0].getProgramatori().size() == 2);
        assert(repo.getTasks()[0].getProgramatori()[0] == "Nume1");
        assert(repo.getTasks()[0].getProgramatori()[1] == "Nume3");
        repo.addTask(Task{11,"descriere11", vector<string>{"Nume1","Nume2"}, "inprogress"});
        assert(repo.getTasks().size() == 11);
        assert(repo.getTasks()[10].getProgramatori()[0] == "Nume1");
        assert(repo.getTasks()[10].getProgramatori()[1] == "Nume2");
        try
        {
            repo.addTask(Task{1,"descriere11", vector<string>{"Nume1","Nume2"}, "inprogress"});
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
    }

    static void testFindRepo()
    {
        copyTargetTemplate("data/test_tasks.txt", "data/default_tasks.txt");
        RepoTasksFile repo("data/test_tasks.txt");
        assert(repo.getTasks().size() == 10);
        auto& t = repo.findTask(1);
        assert(t.getId() == 1);
        assert(t.getDescriere() == "descriere1");
        assert(t.getProgramatori()[0] == "Nume1");
        assert(t.getProgramatori()[1] == "Nume3");
        assert(t.getStare() == "open");
        try
        {
            auto& t1 = repo.findTask(11);
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
    }

    static void testChangeStareRepo()
    {
        copyTargetTemplate("data/test_tasks.txt", "data/default_tasks.txt");
        RepoTasksFile repo("data/test_tasks.txt");
        assert(repo.getTasks().size() == 10);
        auto& t = repo.findTask(1);
        assert(t.getId() == 1);
        assert(t.getDescriere() == "descriere1");
        assert(t.getProgramatori()[0] == "Nume1");
        assert(t.getProgramatori()[1] == "Nume3");
        assert(t.getStare() == "open");
        repo.changeStare(1, "inprogress");
        assert(t.getStare() == "inprogress");
    }

    static void testAddSrv()
    {
        copyTargetTemplate("data/test_tasks.txt", "data/default_tasks.txt");
        RepoTasksFile repo("data/test_tasks.txt");
        Validator val;
        ServiceTasks srv{repo, val};
        assert(srv.getTasks().size() == 10);
        assert(srv.getTasks()[0].getProgramatori().size() == 2);
        assert(srv.getTasks()[0].getProgramatori()[0] == "Nume1");
        assert(srv.getTasks()[0].getProgramatori()[1] == "Nume3");
        srv.addTask(11,"descriere11", vector<string>{"Nume1","Nume2"}, "inprogress");
        assert(srv.getTasks().size() == 11);
        assert(srv.getTasks()[10].getProgramatori()[0] == "Nume1");
        assert(srv.getTasks()[10].getProgramatori()[1] == "Nume2");
        try
        {
            srv.addTask(1,"descriere11", vector<string>{"Nume1","Nume2"}, "inprogress");
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
    }

    static void testFindSrv()
    {
        copyTargetTemplate("data/test_tasks.txt", "data/default_tasks.txt");
        RepoTasksFile repo("data/test_tasks.txt");
        Validator val;
        ServiceTasks srv{repo, val};
        assert(srv.getTasks().size() == 10);
        auto& t = repo.findTask(1);
        assert(t.getId() == 1);
        assert(t.getDescriere() == "descriere1");
        assert(t.getProgramatori()[0] == "Nume1");
        assert(t.getProgramatori()[1] == "Nume3");
        assert(t.getStare() == "open");
        try
        {
            auto& t1 = srv.findTask(11);
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
    }

    static void testSortByStare()
    {
        copyTargetTemplate("data/test_tasks.txt", "data/default_tasks.txt");
        RepoTasksFile repo("data/test_tasks.txt");
        Validator val;
        ServiceTasks srv{repo, val};
        assert(srv.getTasks().size() == 10);
        vector<Task> sorted_tasks = ServiceTasks::sortByStare(srv.getTasks());
        assert(sorted_tasks.size() == 10);
        assert(sorted_tasks[0].getStare() == "closed");
        assert(sorted_tasks[1].getStare() == "closed");
        assert(sorted_tasks[2].getStare() == "inprogress");
        assert(sorted_tasks[3].getStare() == "inprogress");
        assert(sorted_tasks[4].getStare() == "inprogress");
        assert(sorted_tasks[5].getStare() == "inprogress");
        assert(sorted_tasks[6].getStare() == "open");
        assert(sorted_tasks[7].getStare() == "open");
        assert(sorted_tasks[8].getStare() == "open");
        assert(sorted_tasks[9].getStare() == "open");
    }

    static void testFilterByString()
    {
        copyTargetTemplate("data/test_tasks.txt", "data/default_tasks.txt");
        RepoTasksFile repo("data/test_tasks.txt");
        Validator val;
        ServiceTasks srv{repo, val};
        assert(srv.getTasks().size() == 10);
        assert(ServiceTasks::filterByString("1", srv.getTasks()).size() == 4);
    }

    static void testFilterByStare()
    {
        copyTargetTemplate("data/test_tasks.txt", "data/default_tasks.txt");
        RepoTasksFile repo("data/test_tasks.txt");
        Validator val;
        ServiceTasks srv{repo, val};
        assert(srv.getTasks().size() == 10);
        vector<Task> filtered_tasks = ServiceTasks::filterByStare("open", srv.getTasks());
        assert(filtered_tasks.size() == 4);
    }

    static void testChangeStareSrv()
    {
        copyTargetTemplate("data/test_tasks.txt", "data/default_tasks.txt");
        RepoTasksFile repo("data/test_tasks.txt");
        Validator val;
        ServiceTasks srv{repo, val};
        assert(srv.getTasks().size() == 10);
        auto& t = repo.findTask(1);
        assert(t.getId() == 1);
        assert(t.getDescriere() == "descriere1");
        assert(t.getProgramatori()[0] == "Nume1");
        assert(t.getProgramatori()[1] == "Nume3");
        assert(t.getStare() == "open");

        srv.changeStare(1, "inprogress");
        assert(t.getStare() == "inprogress");
    }

public:
    static void testAll()
    {
        testValidate();
        testAddRepo();
        testFindRepo();
        testAddSrv();
        testFindSrv();
        testSortByStare();
        testFilterByString();
        testFilterByStare();
        testChangeStareRepo();
        testChangeStareSrv();
    }
};

#endif //TASKS_TESTS_H

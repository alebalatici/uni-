//
// Created by Alexandra on 5/17/2026.
//

#ifndef DEVICE_TESTS_REPO_H
#define DEVICE_TESTS_REPO_H

#include "../repo/repo_device.h"
#include "../service/service_device.h"
#include "../utils/file_utils.h"
#include <cassert>
class Tests {
private:
    static void test_add_repo()
    {
        FileUtils::copy_target_template("data/test_device.txt", "data/default_device.txt");
        RepoDeviceFile repo("data/test_device.txt");
        int n = (int)repo.get_all_devices().size();
        repo.add_device(Device{"tip1", "model2", 2012, "rosu", 1.0});
        assert(repo.get_all_devices().size() == n + 1);

        try
        {
            repo.add_device(Device{"tip1", "model1", 2001, "rosu", 1.0});
            assert(false);
        }
        catch (std::exception& e)
        {
            assert(true);
        }
    }
    static void test_find_repo()
    {
        FileUtils::copy_target_template("data/test_device.txt", "data/default_device.txt");
        RepoDeviceFile repo("data/test_device.txt");
        Device& device = repo.find_device("model1", "rosu", 1.0);
        assert(device.get_tip() == "tip1");
        assert(device.get_model() == "model1");
        assert(device.get_an() == 2001);
        assert(device.get_culoare() == "rosu");
        assert(device.get_pret() == 1.0);
        try
        {
            Device& d = repo.find_device("model1", "rosu", 3.0);
            assert(false);
        }
        catch (std::exception& e)
        {
            assert(true);
        }
    }

    static void test_add_srv()
    {
        FileUtils::copy_target_template("data/test_device.txt", "data/default_device.txt");
        RepoDeviceFile repo("data/test_device.txt");
        ServiceDevice srv{repo};
        int n = (int)srv.get_all_devices().size();
        srv.add_device("tip1", "model2", 2012, "rosu", 1.0);
        assert(srv.get_all_devices().size() == n + 1);
        try
        {
            srv.add_device("tip1", "model1", 2001, "rosu", 1.0);
            assert(false);
        }
        catch (std::exception& e)
        {
            assert(true);
        }
    }

    static void test_find_srv()
    {
        FileUtils::copy_target_template("data/test_device.txt", "data/default_device.txt");
        RepoDeviceFile repo("data/test_device.txt");
        ServiceDevice srv{repo};
        Device& device = srv.find_device("model1", "rosu", 1.0);
        assert(device.get_tip() == "tip1");
        assert(device.get_model() == "model1");
        assert(device.get_an() == 2001);
        assert(device.get_culoare() == "rosu");
        assert(device.get_pret() == 1.0);
        try
        {
            Device& d = srv.find_device("model1", "galben", 3.0);
            assert(false);
        }
        catch (std::exception& e)
        {
            assert(true);
        }
    }

    static void test_sort_by_model()
    {
        FileUtils::copy_target_template("data/test_device.txt", "data/default_device.txt");
        RepoDeviceFile repo("data/test_device.txt");
        ServiceDevice srv{repo};
        vector<Device> sorted_elems = ServiceDevice::sort_by_model_ascending(srv.get_all_devices());
        assert(sorted_elems[0].get_model() == "model1");
        assert(sorted_elems[9].get_model() == "model9");
    }

    static void test_sort_by_pret()
    {
        FileUtils::copy_target_template("data/test_device.txt", "data/default_device.txt");
        RepoDeviceFile repo("data/test_device.txt");
        ServiceDevice srv{repo};
        vector<Device> sorted_elems = ServiceDevice::sort_by_pret_ascending(srv.get_all_devices());
        assert(sorted_elems[0].get_model() == "model1");
        assert(sorted_elems[9].get_model() == "model10");
    }

public:
    static void test_all()
    {
        test_add_repo();
        test_find_repo();
        test_add_srv();
        test_find_srv();
        test_sort_by_model();
        test_sort_by_pret();
    }
};



#endif //DEVICE_TESTS_REPO_H

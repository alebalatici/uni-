//
// Created by Alexandra on 5/17/2026.
//

#ifndef DEVICE_SERVICE_DEVICE_H
#define DEVICE_SERVICE_DEVICE_H

#include <utility>
#include <algorithm>
#include "../repo/repo_device.h"
using std::sort;
class ServiceException : public std::exception
{
private:
    string message;
public:
    explicit ServiceException(string  message) : message(std::move(message)) {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class ServiceDevice {
private:
    Repo& repo;
public:
    virtual ~ServiceDevice() = default;
    ServiceDevice(Repo& repo) : repo(repo) {}
    ServiceDevice(const ServiceDevice&) = delete;
    ServiceDevice() = delete;

    void add_device(const string& tip, const string& model, int an, const string& culoare, double pret) const
    {
        try
        {
            Device device{tip, model, an, culoare, pret};
            repo.add_device(device);
        }
        catch (std::exception& e)
        {
            throw ServiceException(e.what());
        }
    }

    [[nodiscard]] Device& find_device(const string& model, const string& culoare, double pret) const
    {
        try
        {
            return repo.find_device(model, culoare, pret);
        }
        catch (std::exception& e)
        {
            throw ServiceException(e.what());
        }
    }
    [[nodiscard]] const vector<Device>& get_all_devices() const
    {
        return repo.get_all_devices();
    }

    static vector<Device> sort_by_model_ascending(const vector<Device>& devices)
    {
        vector<Device> sorted_devices = devices;
        sort(sorted_devices.begin(), sorted_devices.end(),[]
            (const Device& a, const Device& b)
            {
                return a.get_model() < b.get_model();
            });

        return sorted_devices;
    }

    static vector<Device> sort_by_pret_ascending(const vector<Device>& devices)
    {
        vector<Device> sorted_devices = devices;
        sort(sorted_devices.begin(), sorted_devices.end(),[]
            (const Device& a, const Device& b)
                {
                    return a.get_pret() < b.get_pret();
                });

        return sorted_devices;
    }
};



#endif //DEVICE_SERVICE_DEVICE_H

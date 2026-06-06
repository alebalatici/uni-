//
// Created by Alexandra on 5/17/2026.
//

#ifndef DEVICE_REPO_DEVICE_H
#define DEVICE_REPO_DEVICE_H

#include <exception>
#include <utility>
#include <algorithm>
#include <vector>
#include "../domain/device.h"
using std::vector;
using std::find_if;
class RepoException : public std::exception {
private:
    string message;
public:
    explicit RepoException(string _message) : message(std::move(_message)) {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class Repo {
public:
    virtual ~Repo() = default;
    Repo() = default;

    virtual void add_device(const Device& device) = 0;
    virtual Device& find_device(const string& model, const string& culoare, double pret) = 0;
    [[nodiscard]] virtual const vector<Device>& get_all_devices() const = 0;
};

class RepoDevice : public Repo {
protected:
    vector<Device> devices;
public:
    /**
     * Adauga un device in memorie
     * @param device Device-ul de adaugat
     */
    void add_device(const Device& device) override
    {
        auto it = find_if(devices.begin(), devices.end(),
            [device](const Device& d)
            {
                return device.get_model() == d.get_model() && device.get_culoare() == d.get_culoare() && device.get_pret() == d.get_pret();
            });
        if (it != devices.end())
        {
            throw RepoException("Device already exists");
        }
        devices.emplace_back(device);
    }

    /**
     * Cauta un device in memorie; Cautarea se realizeaza dupa model, culoare si pret
     * @param model Modelul device-ului de cautat
     * @param culoare Culoarea device-ului de cautat
     * @param pret Pretul device-ului de cautat
     * @return Device-ul cu modelul, culoarea si pretul dat
     */
    Device& find_device(const string& model, const string& culoare, double pret) override
    {
        auto it = find_if(devices.begin(), devices.end(),
            [model, culoare, pret](const Device& d)
            {
                return model == d.get_model() && culoare == d.get_culoare() && pret == d.get_pret();
            });
        if (it == devices.end())
        {
            throw RepoException("Device does not exists");
        }
        return *it;
    }
    [[nodiscard]] const vector<Device>& get_all_devices() const override
    {
        return devices;
    }
};

class RepoDeviceFile : public RepoDevice {
private:
    string filename;
    void load_from_file();
    void save_to_file();
public:
    RepoDeviceFile(string  _filename) : filename{std::move(_filename)}
    {
        load_from_file();
    }
    void add_device(const Device& device) override
    {
        RepoDevice::add_device(device);
        save_to_file();
    }

    Device& find_device(const string& model, const string& culoare, double pret) override
    {
        return RepoDevice::find_device(model, culoare, pret);
    }
    [[nodiscard]] const vector<Device>& get_all_devices() const override
    {
        return RepoDevice::get_all_devices();
    }
};


#endif //DEVICE_REPO_DEVICE_H

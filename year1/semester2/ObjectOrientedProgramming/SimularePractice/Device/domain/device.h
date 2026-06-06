//
// Created by Alexandra on 5/17/2026.
//

#ifndef DEVICE_DEVICE_H
#define DEVICE_DEVICE_H

#include <string>
#include <ostream>
#include <utility>
using std::string;
class Device {
    private:
    string tip;
    string model;
    int an;
    string culoare;
    double pret;
    public:
    Device(string  _tip, string  _model, int _an, string  _culoare, double _pret) : tip{std::move(_tip)}, model{std::move(_model)}, an{_an}, culoare{std::move(_culoare)}, pret{_pret} {};
    Device(const Device& ot) = default;

    friend std::ostream& operator<<(std::ostream& os, const Device& device)
    {
        os << "Tip: " << device.tip << " | Model: " << device.model << " | An: " << device.an << " | Culoare: " << device.culoare << " | Pret: " << device.pret << "\n";
        return os;
    }

    bool operator==(const Device& ot) const
    {
        return ot.tip == tip && ot.model == model && ot.an == an && ot.culoare == culoare && ot.pret == pret;
    }

    [[nodiscard]] string get_tip() const
    {
        return tip;
    }

    [[nodiscard]] string get_model() const
    {
        return model;
    }

    [[nodiscard]] int get_an() const
    {
        return an;
    }

    [[nodiscard]] string get_culoare() const
    {
        return culoare;
    }

    [[nodiscard]] double get_pret() const
    {
        return pret;
    }
};

#endif //DEVICE_DEVICE_H

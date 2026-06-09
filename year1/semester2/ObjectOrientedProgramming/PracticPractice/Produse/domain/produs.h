//
// Created by Alexandra on 5/10/2026.
//

#ifndef PRODUSE_PRODUS_H
#define PRODUSE_PRODUS_H
#include <string>
#include <fstream>
using std::string;
using std::ostream;
class Produs {
private:
        int id;
        string nume;
        string tip;
        double pret;
public:
        Produs(int _id, const string& _nume, const string& _tip, double _pret): id{_id}, nume{_nume}, tip{_tip}, pret{_pret} {}

        bool operator==(const Produs &produs) const
        {
                return this->id == produs.id && this->nume == produs.nume && this->tip == produs.tip && this->pret == produs.pret;
        }

        friend std::ostream& operator<<(ostream &os, const Produs &produs)
        {
                os << "Id: " << produs.id << " | Nume: " << produs.nume << " | Tip: " << produs.tip << " | Pret: " << produs.pret;
                return os;
        }

        [[nodiscard]]int get_id() const;
        [[nodiscard]] string get_nume() const;
        [[nodiscard]] string get_tip() const;
        [[nodiscard]]double get_pret() const;

        void set_nume(const string& nume_nou);
        void set_tip(const string& tip_nou);
        void set_pret(double pret_nou);
};

#endif //PRODUSE_PRODUS_H

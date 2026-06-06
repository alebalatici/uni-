//
// Created by Alexandra on 5/17/2026.
//

#include "repo_device.h"

#include <sstream>

#include "../utils/file_utils.h"

void RepoDeviceFile::load_from_file()
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        throw RepoException("Could not open file");
    }
    string line;
    while (getline(fin, line))
    {
        FileUtils::sanitize(line);
        string tip, model, culoare;
        int an;
        double pret;

        std::stringstream linestream(line);
        string current_item;
        int item_no = 0;
        try
        {
            while (getline(linestream, current_item, ','))
            {
                switch (item_no)
                {
                    case 0: tip = current_item; break;
                    case 1: model = current_item; break;
                    case 2: an = stoi(current_item); break;
                    case 3: culoare = current_item; break;
                    case 4: pret = stod(current_item); break;
                }
                item_no++;
            }
            if (item_no != 5)
            {
                throw RepoException("Formating error on line" + line);
            }
            Device device{tip, model, an, culoare, pret};
            RepoDevice::add_device(device);
        }
        catch (std::exception &e)
        {
            throw RepoException(e.what());
        }
    }
}

void RepoDeviceFile::save_to_file()
{
    ofstream fout(filename);
    if (!fout.is_open())
    {
        throw RepoException("Could not open file");
    }
    for (auto& device : devices)
    {
        fout << device.get_tip() << ',' << device.get_model() << ',' << device.get_an() << ',' << device.get_culoare() << ',' << device.get_pret() << '\n';
    }
}
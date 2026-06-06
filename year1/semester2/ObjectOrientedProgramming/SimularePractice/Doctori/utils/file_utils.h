//
// Created by Alexandra on 5/17/2026.
//

#ifndef DOCTORI_FILE_UTILS_H
#define DOCTORI_FILE_UTILS_H

#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;
class FileUtils {
public:
    /**
     * Elimina caracterele \r de la finalul unui string pentru citirea din fisiere
     * @param s Linia din fisier
     */
    static void sanitize(string& s)
    {
        while (!s.empty() && s.back() == '\r')
        {
            s.pop_back();
        }
    }

    /**
     * Copiaza continutul unui fisier template intr-un fisier target
     * @param target_filename Numele fisierului target
     * @param template_filename Numele fisierului template
     */
    static void copy_target_template(const string& target_filename, const string& template_filename)
    {
        ifstream fin(template_filename);
        ofstream fout(target_filename);
        if (!fin.is_open() || !fout.is_open())
        {
            throw std::runtime_error("Error opening files");
        }
        fout << fin.rdbuf();
        fin.close();
        fout.close();
    }
};

#endif //DOCTORI_FILE_UTILS_H

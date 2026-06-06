//
// Created by Alexandra on 5/17/2026.
//

#ifndef DEVICE_FILE_UTILS_H
#define DEVICE_FILE_UTILS_H

#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;
class FileUtils {
    public:
    static void sanitize(string& s)
    {
        while (!s.empty() && s.back() == '\r')
        {
            s.pop_back();
        }
    }

    static void copy_target_template(const string& target_filename, const string& template_filename)
    {
        ifstream fin(template_filename);
        ofstream fout(target_filename);
        if (!fin.is_open() || !fout.is_open())
        {
             throw std::runtime_error("Error opening file");
        }
        fout << fin.rdbuf();
        fin.close();
        fout.close();
    }
};



#endif //DEVICE_FILE_UTILS_H

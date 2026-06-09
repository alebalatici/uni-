//
// Created by Alexandra on 5/10/2026.
//

#include "file_utils.h"

void FileUtils::sanitize(string& s)
{
    while (s.back() == '\r')
    {
        s.pop_back();
    }
}

void FileUtils::copy_target_template(const string& template_filename, const string& target_filename)
{
    ifstream fin(template_filename);
    ofstream fout(target_filename);
    if (!fin.is_open() || !fout.is_open())
    {
        throw std::runtime_error("Could not open files\n");
    }
    fout << fin.rdbuf();
    fin.close();
    fout.close();
}
//
// Created by Alexandra on 5/9/2026.
//

#include "file_utils.h"
#include <fstream>
using std::ifstream;
using std::ofstream;
void FileUtils::sanitize(string& s)
{
    while (!s.empty() && s.back() == '\r')
    {
        s.pop_back();
    }
}

void FileUtils::copy_target_template(const string& filename_target, const string& filename_template)
{
    ifstream template_file(filename_template);
    ofstream target_file(filename_target);
    if (!target_file.is_open() || !template_file.is_open())
    {
        throw std::runtime_error("Nu se poate deschide fisierul\n");
    }

    target_file << template_file.rdbuf();
    template_file.close();
    template_file.close();
}
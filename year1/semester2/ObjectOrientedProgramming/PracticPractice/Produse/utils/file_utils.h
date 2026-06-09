//
// Created by Alexandra on 5/10/2026.
//

#ifndef PRODUSE_FILE_UTILS_H
#define PRODUSE_FILE_UTILS_H

#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;
class FileUtils {
    public:
    static void sanitize(string& s);
    static void copy_target_template(const string& template_filename, const string& target_filename);
};



#endif //PRODUSE_FILE_UTILS_H

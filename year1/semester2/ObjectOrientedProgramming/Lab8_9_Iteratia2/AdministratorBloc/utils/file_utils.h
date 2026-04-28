#ifndef ADMINISTRATORBLOC_FILE_UTILS_H
#define ADMINISTRATORBLOC_FILE_UTILS_H

#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;

class FileUtils
{
    public:
    static void sanitize(string& s);
    static void copy_template_to_target(const string& target_filename, const string& template_filename);
};

#endif //ADMINISTRATORBLOC_FILE_UTILS_H

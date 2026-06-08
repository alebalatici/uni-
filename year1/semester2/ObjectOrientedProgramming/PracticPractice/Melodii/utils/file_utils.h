//
// Created by Alexandra on 5/9/2026.
//

#ifndef MELODII_FILE_UTILS_H
#define MELODII_FILE_UTILS_H
#include <string>
using std::string;
class FileUtils {
    public:
    static void sanitize(string& s);
    static void copy_target_template(const string& filename_target, const string& filename_template);
};

#endif //MELODII_FILE_UTILS_H

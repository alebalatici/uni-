#include "file_utils.h"

void FileUtils::sanitize(string& s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
}

void FileUtils::copy_template_to_target(const string& target_filename, const string& template_filename)
{
    ifstream temp_file(template_filename);
    ofstream target_file(target_filename);
    if (!target_file.is_open() || !temp_file.is_open())
    {
        throw std::runtime_error("Nu s-au putut deschide fisierele\n");
    }

    string content(
        (std::istreambuf_iterator<char>(temp_file)),
        std::istreambuf_iterator<char>()
    );

    target_file << content;

    target_file.close();
    temp_file.close();
}
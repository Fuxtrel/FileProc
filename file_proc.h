#ifndef FILEPROC_FILE_PROC_H
#define FILEPROC_FILE_PROC_H

#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>

class File_separation{

public:
    File_separation(std::string &command);

    std::string deleteSpace(std::string &command);

    void separation(int count_path, std::string &str);



private:
    std::string file_path;
    std::string key;
    std::string directory_path;
    int path_number;





};





#endif //FILEPROC_FILE_PROC_H

#ifndef FILEPROC_FILE_PROC_H
#define FILEPROC_FILE_PROC_H

#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <boost/filesystem/operations.hpp>
#include <vector>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <fcntl.h>
#include <cstdlib>
namespace bfs = boost::filesystem;

class File_separation{

public:
    explicit File_separation(std::string &command);

    static std::string deleteSpace(std::string &command);

    void separation(int count_path);

    void getFileList();

    void genKeys(char secret[]);

    void decrypt(char secret[]);

    void encrypt();

    std::vector<char*> getFile(int key_size, std::string path, size_t file_size);

    void writeEncodedFile(int key_size, RSA* pubKey, std::vector<char*> file, int file_size);

    void writeDecodedFile(int key_size, RSA* privKey, std::vector<char*> file, int file_size);

private:
    std::string file_path;
    std::string key_directory_path;
    std::string key_file_path_priv;
    std::string key_file_path_pub;
    std::string directory_path;
    int path_number;
    std::vector<std::string> file_list;
    std::ofstream fout;
    std::ifstream fin;


};





#endif //FILEPROC_FILE_PROC_H

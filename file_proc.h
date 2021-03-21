#ifndef FILEPROC_FILE_PROC_H
#define FILEPROC_FILE_PROC_H

#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <vector>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <fcntl.h>
#include <cstdlib>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/detail/push.hpp>
#include <boost/iostreams/detail/push_params.hpp>
#include <zlib.h>
#include <openssl/sha.h>

namespace bfs = boost::filesystem;

class File_separation{

public:
    File_separation(std::string &command);

    File_separation();

    static std::string deleteSpace(std::string &command);

    void separation();

    void defineFileList();

    void genKeys(char secret[]);

    void decrypt(char secret[]);

    void encrypt();

    void unification();

static std::vector<char*> getFile(int key_size, size_t file_size, int size);

    void writeEncodedFile(int key_size, RSA* pubKey, std::vector<char*> file, int file_size);

    void writeDecodedFile(int key_size, RSA* privKey, std::vector<char*> file, int file_size);

    void fileCompress(std::string f_path);

    void fileDecompress(std::string f_path);

    /*  void genKeys_new(char secret[]);*/

    std::vector<std::string> getFileList();

    std::string directory_path;

private:
    std::string file_path;
    std::string key_directory_path;
    std::string key_file_path_priv;
    std::string key_file_path_pub;

    unsigned long path_count;
    std::vector<std::string> file_list;
    std::ofstream fout;
    std::ifstream fin;


};


#endif //FILEPROC_FILE_PROC_H

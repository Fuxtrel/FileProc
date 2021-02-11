#include "file_proc.h"

string deleteSpace(string &command){
    int begin = 0;
    int end = command.length();
    for(int i = 0; command[i] == ' '; i++){
        begin++;
    }
    for(int i = (command.length() - 1); command[i] == ' '; i--){
        end--;
    }
    return command.substr(begin, end - begin);
}

bool separation(string file_path, int count_path){
    FILE *file;
    file = fopen(file_path.c_str(), "rb");
    if (file == nullptr) {
        puts ("не удалось открыть файл");
        getchar(); exit (1);
    }
    fseek (file, 0, SEEK_END);
    cout << ftell (file);
    return true;
}

string getFilePath(string &str){
    int tmp_pos = 0;
    for(int i = 0; str[i] != ' '; i++){
        tmp_pos = i;
    }
    return str.substr(0, tmp_pos);
}
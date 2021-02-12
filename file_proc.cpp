#include "file_proc.h"

void skipSpaces(int &i, std::string &str){
    i++;
    while((str[i] == ' ') && (i < str.length())){
        i++;
    }
}

std::string File_separation::deleteSpace(std::string &command){
    int begin = 0;
    int end = command.length();
    for(int i = 0; command[i] == ' '; i++){
        begin++;
    }
    for(size_t i = (command.length() - 1); command[i] == ' '; i--){
        end--;
    }
    return command.substr(begin, end - begin);
}

void File_separation::separation(int count_path, std::string &file_path){
    std::ifstream fin(file_path.c_str(), std::ios::in);
    if (fin.is_open()){
        std::cout << "File is correct open\n";
    }else{
        perror("File is not open\n");
        std::cout << file_path;
    }
    std::streampos begin,end;
    fin.seekg (0, std::ios::beg);
    begin = fin.tellg();
    fin.seekg (0, std::ios::end);
    end = fin.tellg();
    fin.close();
    std::cout << "Size of file: " << (end - begin) << " Bytes.\n";
}





File_separation::File_separation(std::string &command) {
    std::string str = deleteSpace(command);
    std::cout << str << std::endl;
    for(int i = 0; i < str.length(); i++){
        if(str[i] == '-'){
            i++;
            char tmp = str[i];
            switch(int(tmp)){
                case int('c'):

                    break;
                case int('b'):

                    break;
                case int('k'):
                    skipSpaces(i, str);
                    for(; (str[i] != ' ') && (i < str.length()); i++){
                        file_path += str[i];
                    }
                    std::cout << "file_path: " << file_path << std::endl;
                    break;
                case int('f'):
                    skipSpaces(i, str);
                    for(; (str[i] != ' ') && (i < str.length()); i++){
                        file_path += str[i];
                    }
                    std::cout << "file_path: " << file_path << std::endl;

                    break;
                case int('d'):
                    skipSpaces(i, str);
                    for(; str[i] != ' '; i++){
                        directory_path += str[i];
                        std::cout << "directory_path: " << directory_path << std::endl;
                    }
                    break;
                case int('n'):
                    skipSpaces(i, str);
                    path_number = std::stoi(str.substr(i));
                    std::cout << "path_number: " << path_number << std::endl;
                    break;
                default:
                    perror("Not correct key");

                    break;
            }
        }
    }

}
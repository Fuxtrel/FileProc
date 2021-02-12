#include "file_proc.h"



int main() {
    setlocale(LC_ALL, "rus");
    std::string command = R"(-d /home/alex/CLionProjects/FileProc)";
    //getline(std::cin, command);
    std::cout << command << std::endl;
    File_separation fil(command);
    fil.getFileList();
    std::cout << "------------------------Шифрование RSA------------------------" << std::endl;
    std::cout << "1. Получение ключей" << std::endl;
    std::cout << "2. Зашифровать содержимое файла" << std::endl;
    std::cout << "3. Дешифровать содержимое файла" << std::endl;
    std::cout << "4. Выйти ESC" << std::endl;
    int choice;
    std::cin >> choice;
    switch(choice){
        case 1:
            fil.genKeys("123");
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:
            exit(1);
            break;
    }


}

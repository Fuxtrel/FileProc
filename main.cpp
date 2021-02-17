#include "file_proc.h"



int main() {
    setlocale(LC_ALL, "rus");
    std::string command = R"(-k /home/alex/CLionProjects/FileProc -f /home/alex/CLionProjects/FileProc/test_file.txt -d /home/alex/CLionProjects/FileProc)";
    //getline(std::cin, command);
    std::cout << command << std::endl;
    File_separation fil(command);
    //fil.getFileList();
    std::cout << "------------------------Шифрование RSA------------------------" << std::endl;
    std::cout << "1. Получение ключей" << std::endl;
    std::cout << "2. Зашифровать содержимое файла" << std::endl;
    std::cout << "3. Дешифровать содержимое файла" << std::endl;
    std::cout << "4. Выйти ESC" << std::endl;
    char secret[] = {1,2,3};
    fil.separation(2);

    fil.genKeys(secret);
    fil.encrypt();
    fil.decrypt(secret);

   /* int choice;
    std::cin >> choice;
    switch(choice){
        case 1:
            fil.genKeys(secret);
            fil.encrypt();
            fil.decrypt(secret);
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:
            exit(1);
            break;
    }*/

}

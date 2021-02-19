#include "file_proc.h"



int main() {
    setlocale(LC_ALL, "rus");
    std::string command = R"(-k /home/alex/CLionProjects/FileProc -f /home/alex/CLionProjects/FileProc/test_file.txt -d /home/alex/CLionProjects/FileProc)";
    while(true) {
        std::cout << "------------------------Шифрование RSA------------------------" << std::endl;
        std::cout << "1. Получение ключей" << std::endl;
        std::cout << "2. Зашифровать содержимое файла" << std::endl;
        std::cout << "3. Дешифровать содержимое файла" << std::endl;
        std::cout << "4. Выйти" << std::endl;
        char secret[] = {1, 2, 3};

        int choice;
        std::cout << "Выберите действие...\n";
        std::cin >> choice;
        std::cout << "-d путь до папки -f файла -k путь до папки с ключами -c/-b\n";
        std::cin.get();
        getline(std::cin, command);
        File_separation fil(command);
        switch (choice) {
            case 1:
                fil.genKeys(secret);
                break;
            case 2:
                fil.encrypt();
                fil.separation();
                break;
            case 3:
                fil.unification();
                fil.decrypt(secret);
                break;
            case 4:
                exit(1);
        }
    }
}

#include "file_proc.h"


int main() {

    setlocale(LC_ALL, "rus");
    std::string command = R"(-k /home/alex/Документы/Dir -f /home/alex/Документы/Dir/test_file.txt -d /home/alex/Документы/Dir/res)";
    while(true) {
        std::cout << "------------------------Шифрование RSA------------------------" << std::endl;
        std::cout << "1. Получение ключей" << std::endl;
        std::cout << "2. Зашифровать содержимое файла" << std::endl;
        std::cout << "3. Дешифровать содержимое файла" << std::endl;
        std::cout << "4. Выйти" << std::endl;
        char secret[] = {1, 2, 3};

        std::string choice;
        std::cout << "Выберите действие...\n";
        std::cin >> choice;
        while(true) {
            if (choice.length() == 1) {
                if ((choice[0] == '1') || (choice[0] == '2') || (choice[0] == '3') || (choice[0] == '4')) {
                    break;
                }else{
                    std::cout << "Неправильный номер действия\n"
                                 "Введите номер заново\n";
                    std::cin >> choice;
                }
            } else {
                std::cout << "Неправильный номер действия\n"
                             "Введите номер заново\n";
                std::cin >> choice;
            }
        }
        if(choice[0] == '4'){
            exit(1);
        }
        std::cout << "Введите необходимые пути\n"
                     "-d путь до ПАПКИ, где лежат или будут лежать закодированные файлы\n"
                     "-f путь к ФАЙЛУ, который надо закодировать или где будет лежать раскодированный файл\n"
                     "-k путь до ПАПКИ с ключами\n"
                     "-n ЧИСЛО частей, на который будет разбит закодированный файл\n";
        std::cin.get();
        getline(std::cin, command);
        File_separation fil(command);
        switch (stoi(choice)) {
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
        }
    }
}

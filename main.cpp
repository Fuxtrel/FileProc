#include "file_proc.h"

int main() {
    setlocale(LC_ALL, "rus");
    std::cout << "Start processing, input the command\n";
    std::string command = R"(-f C:\Users -n 5dfkvjbkj)";
    //getline(std::cin, command);
    std::cout << command << std::endl;
    File_separation fil(command);


}

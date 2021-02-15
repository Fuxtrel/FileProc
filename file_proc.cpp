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

void File_separation::separation(int count_path){
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
                        key_directory_path += str[i];
                    }
                    key_file_path_priv = key_directory_path + "/private.key";
                    key_file_path_pub = key_directory_path + "/public.key";


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
                    for(; (str[i] != ' ') && (i < str.length()); i++){
                        directory_path += str[i];
                    }
                    std::cout << "directory_path: " << directory_path << std::endl;
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

void File_separation::getFileList() {
    boost::filesystem::directory_iterator begin(directory_path);
    boost::filesystem::directory_iterator end;
    boost::filesystem::file_status fs = boost::filesystem::status(*begin);
    int i = 0;
    for(bfs::directory_iterator begin("/home/alex/Изображения"), end; begin != end; ++begin, i++)
    {
        file_list.push_back(begin->path().filename().string());
        std::cout << file_list[i] << " ";
        std::cout << bfs::file_size(begin->path()) << " Byte" << std::endl;
    }

}



void File_separation::genKeys(char secret[]){
    /* указатель на структуру для хранения ключей */

    RSA * rsa = nullptr;
    int bits = 1024; /* длина ключа в битах */
    FILE* privKey_file = nullptr;
    FILE* pubKey_file = nullptr;

    /* контекст алгоритма шифрования */

    const EVP_CIPHER *cipher = nullptr;

    /*Создаем файлы ключей*/

    privKey_file = fopen(key_file_path_priv.c_str(), "wb");
    pubKey_file = fopen(key_file_path_pub.c_str(), "wb");

    /* Генерируем ключи */

    rsa = RSA_generate_key(bits, RSA_F4, nullptr, nullptr);

    /* Формируем контекст алгоритма шифрования */

    cipher = EVP_get_cipherbyname("bf-ofb");

    /* Получаем из структуры rsa открытый и секретный ключи и сохраняем в файлах.
    * Секретный ключ шифруем с помощью парольной фразы
    */
    PEM_write_RSAPrivateKey(privKey_file, rsa, cipher, nullptr, 0, nullptr, secret);
    PEM_write_RSAPublicKey(pubKey_file, rsa);
    /* Освобождаем память, выделенную под структуру rsa */
    RSA_free(rsa);
    fclose(privKey_file);
    fclose(pubKey_file);
    std::cout << "Ключи сгенерированы и помещены в папку" << key_directory_path << std::endl;
}


void File_separation::encrypt(){
//структура для хранения открытого ключа

    RSA * pubKey = nullptr;
    FILE * pubKey_file = nullptr;

//Считываем открытый ключ

    pubKey_file = fopen(key_file_path_pub.c_str(), "rb");
    pubKey = PEM_read_RSAPublicKey(pubKey_file, nullptr, nullptr, nullptr);
    fclose(pubKey_file);

//Определяем длину ключа

    int key_size = RSA_size(pubKey);

//Шифруем содержимое входного файла
    std::vector<std::string> file;

    fin.open(file_path, std::ios::in);
    if(!fin.is_open()){
        perror("Файл не открыт");
        exit(-1);
    }
    std::string tmp;
    while(!fin.eof()){
        getline(fin, tmp);
        if(tmp.size() > (key_size - 11)){
            std::string tmp1[2];
            tmp1[0] = tmp.substr(0, tmp.size()/2);
            tmp1[1] = tmp.substr(tmp.size()/2);
            file.push_back(tmp1[0]);
            file.push_back(tmp1[1]);
        }else if(tmp.size() >= 0 && tmp.size() < (key_size - 11)){
            file.push_back(tmp);
        }else{
            perror("Ошибка размера считывания файла");
            exit(-1);
        }
    }
    fin.close();

    fout.open(directory_path + "/encoded.file", std::ios::out);
    if(!fout.is_open()){
        perror("Файл не открыт");
        exit(-1);
    }
    unsigned char result[key_size];
    for(int i = 0; i < file.size(); i++){
        RSA_public_encrypt(file[i].size(), (unsigned char *)file[i].c_str(), result, pubKey, RSA_PKCS1_PADDING);
        for(int i = 0; result[i] != '\0'; i++){
            fout << result[i];
        }
        fout << std::endl;
    }
    fout.close();

    std::cout << "Содержимое файла test.file было зашифровано и помещено в файл encoded.file" << std::endl;
}

void File_separation::decrypt(char secret[]){
    RSA * privKey = nullptr;
    FILE * privKey_file;

//Открываем ключевой файл и считываем секретный ключ

    OpenSSL_add_all_algorithms();
    privKey_file = fopen(key_file_path_priv.c_str(), "rb");
    privKey = PEM_read_RSAPrivateKey(privKey_file, nullptr, nullptr, secret);

//Определяем размер ключа

    int key_size = RSA_size(privKey);
    fin.open(directory_path + "/encoded.file", std::ios::in);
    if(!fin.is_open()){
        perror("Файл не открыт");
        exit(-1);
    }
    std::cout << directory_path + "/encoded.file" << std::endl;
    std::vector<std::string> file;
    std::string tmp;
    while(!fin.eof()){
        getline(fin, tmp);
        if(tmp.size() > (key_size - 11)){
            std::string tmp1[2];
            tmp1[0] = tmp.substr(0, tmp.size()/2);
            tmp1[1] = tmp.substr(tmp.size()/2);
            file.push_back(tmp1[0]);
            file.push_back(tmp1[1]);
        }else if(tmp.size() >= 0 && tmp.size() < (key_size - 11)){
            file.push_back(tmp);
        }else{
            perror("Ошибка размера считывания файла");
            exit(-1);
        }
    }
    fin.close();

//Дешифруем файл

    fout.open(directory_path + "/decoded.file", std::ios::out);
    if(!fout.is_open()){
        perror("Файл не открыт");
        exit(-1);
    }
    for(int i = 0; i < file.size(); i++){
        if(RSA_private_decrypt(file[i].size(), (unsigned char *)file[i].c_str(), (unsigned char *)tmp.c_str(), privKey, RSA_PKCS1_PADDING) == -1){
            perror("Не удалось расшифровать");
            exit(-1);
        }
        fout << tmp;
        std::cout << file[i] << std::endl;
    }
    fout.close();
    std::cout << "Содержимое файла encoded.file было дешифровано и помещено в файл decoded.file" << std::endl;

}

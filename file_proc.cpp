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

void File_separation::separation(int count_path) {
    size_t file_size = bfs::file_size(file_path);
    fin.open(file_path, std::ios::binary | std::ios::in);
    if(!fin.is_open()){
        perror("Файл не открыт");
    }
    for(int i = 0; i < count_path - 1; i++){
        char buffer[(file_size / count_path) + 1];
        fin.read(buffer, (file_size / count_path));
        fout.open(directory_path + "/part" + std::to_string(i + 1) + ".txt");
        if(!fout.is_open()){
            perror("Файл не открыт");
        }
        fout.write(buffer, (file_size / count_path));
        fout.close();
    }
    int tmp_beg = fin.tellg();
    fin.seekg(0, std::ios::end);
    int tmp_end = fin.tellg();
    fin.seekg(tmp_beg, std::ios::beg);
    char buffer[tmp_end - tmp_beg + 1];
    fin.read(buffer, (tmp_end - tmp_beg));
    fout.open(directory_path + "/part" + std::to_string(count_path) + ".txt");
    fout.write(buffer, (tmp_end - tmp_beg));
    fout.close();
    fin.close();
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
    pubKey_file = fopen(key_file_path_pub.c_str(), "rb");
    pubKey = PEM_read_RSAPublicKey(pubKey_file, nullptr, nullptr, nullptr);
    fclose(pubKey_file);
    int key_size = RSA_size(pubKey);

//Шифруем содержимое входного файла

    size_t file_size = bfs::file_size(file_path);
    std::vector<char*> file = getFile(key_size, file_path, file_size);
    writeEncodedFile(key_size, pubKey, file, file_size);

    std::cout << "Содержимое файла test_file.txt было зашифровано и помещено в файл encoded.file" << std::endl;
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
    size_t file_size = bfs::file_size(directory_path + "/encoded.file");
    std::vector<char*> file = getFile(key_size, directory_path + "/encoded.file", file_size);
    writeDecodedFile(key_size,privKey, file, file_size);

    std::cout << "Содержимое файла encoded.file было дешифровано и помещено в файл decoded.file" << std::endl;

}

std::vector<char*> File_separation::getFile(int key_size, std::string path, size_t file_size) {
    int size_of_vector;
    if(file_size % (key_size - 11)){
        size_of_vector = file_size / (key_size - 11) + 1;
    }else{
        size_of_vector = file_size / (key_size - 11);
    }
    std::vector<char*> file(size_of_vector);
    for(int i = 0; i < file_size / (key_size - 11); i++){
        file[i] = new char[key_size - 11];
    }
    if(file_size % (key_size - 11)){
        file[file.size() - 1] = new char[file_size % (key_size - 11)];
    }

    fin.open(path, std::ios::in);
    if(!fin.is_open()){
        perror("Файл не открыт");
        exit(-1);
    }
    for(int i = 0; i < file.size() - 1; i++){
        fin.read(file[i], (key_size - 11));
    }
    if(file_size % (key_size - 11)){
        fin.read(file[file.size() - 1], file_size % (key_size - 11));
    }
    std::cout.write(file[file.size() - 1], file_size % (key_size - 11));
    std:: cout << std::endl;
    fin.close();
    return file;
}

void File_separation::writeEncodedFile(int key_size, RSA* pubKey, std::vector<char*> file, int file_size) {
    fout.open(directory_path + "/encoded.file", std::ios::out);
    if(!fout.is_open()){
        perror("Файл не открыт");
        exit(-1);
    }
    char result[key_size - 11];
    for(int i = 0; i < file.size() - 1; i++){
        RSA_public_encrypt((key_size - 11), (unsigned char *)file[i], (unsigned char*)result, pubKey, RSA_PKCS1_PADDING);
        fout.write(result, key_size - 11);
    }
    if(file_size % (key_size - 11)){
        char result_[file_size % (key_size - 11)];
        RSA_public_encrypt((file_size % (key_size - 11)), (unsigned char *)file[file.size() - 1], (unsigned char*)result_, pubKey, RSA_PKCS1_PADDING);
        fout.write(result_, file_size % (key_size - 11));
        std::cout.write(result_, file_size % (key_size - 11));
        std:: cout << std::endl;
    }
    fout.close();
}

void File_separation::writeDecodedFile(int key_size, RSA *privKey, std::vector<char *> file, int file_size) {
    fout.open(directory_path + "/decoded.file", std::ios::out);
    if(!fout.is_open()){
        perror("Файл не открыт");
        exit(-1);
    }
    char result[key_size - 11];
    for(int i = 0; i < file.size() - 1; i++){
        RSA_public_encrypt((key_size - 11), (unsigned char *)file[i], (unsigned char*)result, privKey, RSA_PKCS1_PADDING);
        fout.write(result, key_size - 11);
    }
    if(file_size % (key_size - 11)){
        char result_[file_size % (key_size - 11)];
        if(RSA_private_decrypt((file_size % (key_size - 11)), (unsigned char *)file[file.size() - 1], (unsigned char*)result_, privKey, RSA_PKCS1_PADDING) == -1) {
            perror("Не удалось расшифровать");

            exit(-1);
        }
        fout.write(result_, file_size % (key_size - 11));
        std::cout.write(result_, file_size % (key_size - 11));
        std:: cout << std::endl;
    }
    fout.close();
}

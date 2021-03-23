#include "gtest/gtest.h"
#include "../file_proc.h"

double Double (const double){

}

TEST(DeleteSpaces, FirstAndLastSpace){
    std::string str = " home/alex ";
    File_separation bil;
    ASSERT_STREQ("home/alex", bil.deleteSpace(str).c_str());
}

TEST(DeleteSpaces, ManySpaceAndLastSpace){
    std::string str = "   home/alex ";
    File_separation bil;
    ASSERT_STREQ("home/alex", bil.deleteSpace(str).c_str());
}

TEST(DeleteSpaces, FirstAndLastManySpace){
    std::string str = " home/alex   ";
    File_separation bil;
    ASSERT_STREQ("home/alex", bil.deleteSpace(str).c_str());
}

TEST(Encripting, EmptyWriting){
    RSA * rsa = nullptr;
    int bits = 1024; /* длина ключа в битах */
    FILE* privKey_file = nullptr;
    FILE* pubKey_file = nullptr;
    const EVP_CIPHER *cipher = nullptr;
    privKey_file = fopen(key_file_path_priv.c_str(), "wb");
    pubKey_file = fopen(key_file_path_pub.c_str(), "wb");
    rsa = RSA_generate_key(bits, RSA_F4, nullptr, nullptr);
    cipher = EVP_get_cipherbyname("bf-ofb");
    ASSERT_ANY_THROW(!PEM_write_RSAPrivateKey(privKey_file, rsa, cipher, nullptr, 0, nullptr, secret));


}

TEST




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
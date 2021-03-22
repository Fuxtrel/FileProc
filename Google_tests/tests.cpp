#include "gtest/gtest.h"
#include "../file_proc.h"

File_separation::File_separation(){
    directory_path = "/home/alex/CLionProjects/FileProc/Google_tests/tmp_tests";
    key_file_path_priv = "/home/alex/CLionProjects/FileProc/Google_tests/tmp_tests/priv.key";
    key_file_path_pub = "/home/alex/CLionProjects/FileProc/Google_tests/tmp_tests/pub.key";
    file_path = "/home/alex/CLionProjects/FileProc/Google_tests/tmp_tests/test_file.txt";
    key_directory_path = "/home/alex/CLionProjects/FileProc/Google_tests/tmp_tests";
}

File_separation::File_separation(std::string file_path,
                                 std::string key_directory_path,
                                 std::string key_file_path_priv,
                                 std::string key_file_path_pub,
                                 std::string directory_path) {
    directory_path = directory_path;
    file_path = file_path;
    key_directory_path = key_directory_path;
    key_file_path_pub = key_file_path_pub;
    key_file_path_priv = key_file_path_priv;
}

TEST(Files, get_file_name){
    std::string file_names[2] = {"res", "test_file.txt"};
    File_separation bil;
    bil.defineFileList();
    std::vector<std::string> file_list = bil.getFileList();
    for(int i = 0; i < file_list.size(); i++){
        ASSERT_STREQ(file_names[i].c_str(), file_list[i].c_str());
    }
}



TEST(Command_convert, spaces_before) {
    File_separation bil;
    std::string command = " test";
    ASSERT_STREQ("test", bil.deleteSpace(command).c_str());
}

TEST(Command_convert, spaces_after) {
    File_separation bil;
    std::string command = "test ";
    ASSERT_STREQ("test", bil.deleteSpace(command).c_str());
}

TEST(Command_convert, spaces_before_after) {
    File_separation bil;
    std::string command = " test ";
    ASSERT_STREQ("test", bil.deleteSpace(command).c_str());
}

TEST(Command_convert, without_spaces) {
    File_separation bil;
    std::string command = "test";
    ASSERT_STREQ("test", bil.deleteSpace(command).c_str());
}

TEST(Command_convert, spaces_more_one_after_more_one_before) {
    File_separation bil;
    std::string command = "  test  ";
    ASSERT_STREQ("test", bil.deleteSpace(command).c_str());
}

TEST(Command_convert, spaces_more_one_after_one_before) {
    File_separation bil;
    std::string command = " test  ";
    ASSERT_STREQ("test", bil.deleteSpace(command).c_str());
}

TEST(Command_convert, spaces_one_after_more_one_before) {
    File_separation bil;
    std::string command = "  test ";
    ASSERT_STREQ("test", bil.deleteSpace(command).c_str());
}

TEST(Command_convert, command_empty) {
    File_separation bil;
    std::string command = "";
    ASSERT_DEATH(bil.deleteSpace(command), "!command.empty().*");
}

TEST(Encoding, write_pub_priv_keys) {
    File_separation bil;
    char secret[] = {'1', '2', '3'};
    ASSERT_NO_THROW(bil.genKeys(secret));
}

TEST(Encoding, count_encoded_bytes) {
    File_separation bil;
    ASSERT_NO_THROW(bil.encrypt());
}

TEST(Decoding, eq_decocded_vs_original){
    File_separation bil;


}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



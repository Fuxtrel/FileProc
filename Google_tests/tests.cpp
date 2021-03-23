#include "gtest/gtest.h"
#include "../file_proc.h"

namespace bfs = boost::filesystem;


File_separation::File_separation() {
    boost::filesystem::path full_path(boost::filesystem::current_path());
    directory_path = full_path.string() + "/tmp_tests";
    key_file_path_priv = full_path.string() + "/tmp_tests/priv.key";
    key_file_path_pub = full_path.string() + "/tmp_tests/pub.key";
    file_path = full_path.string() + "/tmp_tests/test_file.txt";
    key_directory_path = full_path.string() + "/tmp_tests";


}

File_separation::File_separation(std::string path,
                                 std::string key_dirpath,
                                 std::string key_filepath_priv,
                                 std::string key_filepath_pub,
                                 std::string dirpath) :
        directory_path(dirpath),
        file_path(path),
        key_directory_path(key_dirpath),
        key_file_path_pub(key_filepath_pub),
        key_file_path_priv(key_filepath_priv) {}

TEST(Files, get_file_name){
    std::string file_names[3] = {"progress.marks", "CMakeDirectoryInformation.cmake", "Google_Tests_run.dir"};
    File_separation bil("", "", "", "", "/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/CMakeFiles");
    bil.defineFileList();
    std::vector <std::string> file_list = bil.getFileList();
    for(int i = 0; i<file_list.size(); i++){
        ASSERT_STREQ(file_names[i].c_str(), file_list[i].c_str());
    }
}


TEST(Command_convert, spaces_before) {
    File_separation bil;
    std::string command = " test";
    ASSERT_STREQ("test", bil.
    deleteSpace(command).c_str());
}

TEST(Command_convert, spaces_after) {
    File_separation bil;
    std::string command = "test ";
    ASSERT_STREQ("test", bil.
    deleteSpace(command).c_str());
}

TEST(Command_convert, spaces_before_after
) {
    File_separation bil;
    std::string command = " test ";
    ASSERT_STREQ("test", bil.
    deleteSpace(command).c_str());
}

TEST(Command_convert, without_spaces) {
    File_separation bil;
    std::string command = "test";
    ASSERT_STREQ("test", bil.
    deleteSpace(command).c_str());
}

TEST(Command_convert, spaces_more_one_after_more_one_before) {
    File_separation bil;
    std::string command = "  test  ";
    ASSERT_STREQ("test", bil.deleteSpace(command).c_str());
}

TEST(Command_convert, spaces_more_one_after_one_before) {
    File_separation bil;
    std::string command = " test  ";
    ASSERT_STREQ("test", bil.
    deleteSpace(command).c_str());
}

TEST(Command_convert, spaces_one_after_more_one_before) {
    File_separation bil;
    std::string command = "  test ";
    ASSERT_STREQ("test", bil.
    deleteSpace(command).c_str());
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

TEST(Decoding, decoded){
    File_separation bil(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/res/res.txt)",
                        R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests)",
                        R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/priv.key)",
                        R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/priv.key)",
                        R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests)"
                        );
    char secret[] = {'1', '2', '3'};
    ASSERT_NO_THROW(bil.decrypt(secret));
}

TEST(Decoding, eq_original){
    std::ifstream fin_dec(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/res/res.txt)", std::ios::in | std::ios::binary);
    std::ifstream fin_orig(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/test_file.txt)", std::ios::in | std::ios::binary);
    int size_dec = boost::filesystem::file_size(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/res/res.txt)");
    int size_orig = boost::filesystem::file_size(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/test_file.txt)");
    EXPECT_EQ(size_dec, size_orig);
    char dec[size_dec];
    char orig[size_orig];
    fin_dec.read(dec, size_dec);
    fin_orig.read(orig, size_orig);
    for(int i = 0; i < size_dec; i++){
        EXPECT_EQ(dec[i], orig[i]);
    }
    fin_dec.close();
    fin_orig.close();
}

TEST(File_compress, size_of_file_compress)
{
    File_separation bil(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/test_file.txt)", "", "", "", "");
    ASSERT_NO_THROW(bil.fileCompress(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/test_file.txt)"));
    int size_b = boost::filesystem::file_size(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/test_file.txt)");
    int size_a = boost::filesystem::file_size(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/test_file.txt.gzip)");
    ASSERT_LE(size_a, size_b);
}

TEST(File_decompress, size_of_file_decompress){
    File_separation bil("", "", "", "", "");
    ASSERT_NO_THROW(bil.fileDecompress(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/test_file.txt.gzip)"));
    int size_a = boost::filesystem::file_size(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/test_file(1).txt)");
    int size_b = boost::filesystem::file_size(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/test_file.txt.gzip)");
    int size_et = boost::filesystem::file_size(R"(/home/alex/CLionProjects/FileProc/cmake-build-debug/Google_tests/tmp_tests/test_file.txt)");
    ASSERT_LE(size_b, size_a);
    ASSERT_EQ(size_a, size_et);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



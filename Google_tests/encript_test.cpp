#include "gtest/gtest.h"
#include "../file_proc.h"

File_separation::File_separation(){
    directory_path = "/home/alex/Загрузки/GGTEST";
}

TEST(First, first_test){
    File_separation bil;
    bil.defineFileList();
    std::vector<std::string> file_list = bil.getFileList();
    for(int i = 0; i < file_list.size(); i++){
        std::cout << file_list[i] << std::endl;
    }

}

TEST(First1, second_test){
    ASSERT_EQ(123, 123);
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



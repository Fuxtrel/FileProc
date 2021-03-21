# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} #[[${Boost_INCLUDE_DIRS}]])

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run encript_test.cpp separation_test.cpp compress_test.cpp ../file_proc.h ../file_proc.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)
target_link_libraries(Google_Tests_run)

link_directories(Google_Tests_run ${Boost_LIBRARY_DIRS})
target_link_libraries (Google_Tests_run ${Boost_LIBRARIES})

target_link_libraries(Google_Tests_run ZLIB::ZLIB)

link_directories(Google_Tests_run ${OpenSSL_LIBRARY_DIRS})
target_link_libraries (Google_Tests_run OpenSSL::SSL)

# 'Google_test' is the subproject name
project(Google_tests)

# 'lib/googletest' is the folder with Google Test sources
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
add_executable(Google_Tests_run init/init.cpp matrix/test_matrix.cpp layer/test_layer.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)
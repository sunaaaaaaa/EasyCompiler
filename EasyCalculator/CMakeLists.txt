cmake_minimum_required(VERSION 2.8)

project(easycal)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

#set命令将第二行开始的文件添加到变量LIB_SRC中去，可以通过${}取出
set(LIB_SRC
   lexer/lexer.cc
   )

include_directories(.)
#生成动态库或者静态库，第一个参数指定库的名字，第二个参数决定是静态库还是动态库，shared为动态库  
#第三个为生成库的源文件
add_library(easycal SHARED ${LIB_SRC})
set(LIB_LIB
   easycal
   )

add_executable(test test.cc)
add_dependencies(test easycal)
target_link_libraries(test ${LIB_LIB})

#EXECUTABLE_OUTPUT_PATH 和 PROJECT_SOURCE_DIR 为CMake自带的预定义的变量，分别表示二进制可执行文件的存放位置和工程根目录
#LIBRARY_OUTPUT_PATH 该变量同样是预先定义好的，表示库文件的输出位置
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

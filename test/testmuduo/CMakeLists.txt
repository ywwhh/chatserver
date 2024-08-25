
# 配置头文件搜素路径
# include_directories()
# 配置库文件搜索路径
# link_directories()

# 设置需要编译的源文件
#add_executable(server muduo_server.cpp)

# 设置需要编译的源文件列表
set(SRC_LIST ./muduo_server.cpp)

# 设置可执行文件最终存储路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 配置头文件的搜索路径
#include_directories(${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/include/server)

# 加载子目录
add_executable(server ${SRC_LIST})

target_link_libraries(server muduo_net muduo_base pthread)

cmake_minimum_required(VERSION 3.0)
project(main)

#配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置头文件搜素路径
# include_directories()
# 配置库文件搜索路径
# link_directories()

# 设置需要编译的源文件
# add_executable(server muduo_server.cpp)

# 设置需要编译的源文件列表
# set(SRC_LIST ./muduo_server.cpp)

# 设置可执行文件最终存储路径
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 配置头文件的搜索路径
#include_directories(${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/include/server)

# 加载子目录
add_subdirectory(testmuduo)
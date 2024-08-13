# 这是一个主CMakeList
cmake_minimum_required(VERSION 3.10)
project(Logger)

# 增加clangd的配置
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_subdirectory(lib)
add_subdirectory(third_party/spdlog)
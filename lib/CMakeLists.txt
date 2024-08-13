# 将当前路径下的Logger.cpp编译为Logger库，引用根目录下的include路径

add_library(Logger STATIC Logger.cpp)
target_link_libraries(Logger PUBLIC spdlog)
target_include_directories(Logger PUBLIC ${CMAKE_SOURCE_DIR}/include)
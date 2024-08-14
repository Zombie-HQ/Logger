add_library(Logger STATIC Logger.cpp)
target_link_libraries(Logger PUBLIC spdlog)
target_include_directories(Logger PUBLIC ${CMAKE_SOURCE_DIR}/include)
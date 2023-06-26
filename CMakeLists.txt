cmake_minimum_required(VERSION 3.0)
project (cpp_test)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_DIR lib/x86_64-w64-mingw32)

add_executable(cpp_test main.cpp)

include_directories(${SDL2_DIR}/include)

link_directories(${SDL2_DIR}/lib)

target_link_libraries(cpp_test SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
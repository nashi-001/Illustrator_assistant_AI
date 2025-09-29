cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(MyTorchApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "C:/libtorch")  # libtorch を解凍したパスに変更

find_package(Torch REQUIRED)

add_executable(myapp main.cpp)
target_link_libraries(myapp "${TORCH_LIBRARIES}")
target_compile_features(myapp PRIVATE cxx_std_17)

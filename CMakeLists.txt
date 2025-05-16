cmake_minimum_required(VERSION 3.10)
project(stack LANGUAGES CXX)

# Собираем библиотеку из исходников stack

add_library(stack STATIC
    "src/stack_err_proc.cpp
    src/stack_funcs.cpp
    src/stack_output.cpp"
)

target_include_directories(stack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(stack PUBLIC cxx_std_17)


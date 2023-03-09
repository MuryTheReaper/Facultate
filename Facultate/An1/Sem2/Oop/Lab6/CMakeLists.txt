cmake_minimum_required(VERSION "3.18.4")

set(PROJECT_NAME Lab6)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=-*,cppcoreguidelines-*,-cppcoreguidelines-pro-bounds-array-to-pointer-decay")
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy checks=-*,cppcoreguidelines-*,-cppcoreguidelines-pro-bounds-array-to-pointer-decay")

add_executable("c_app" "main.cpp" "disciplina.cpp" "repository.cpp" "services.cpp" "ui.cpp" "validator.cpp" "teste.cpp" "my_vector.cpp" "contract.cpp" "raport.cpp" "undo.cpp")

set(CMAKE_CXX_FLAGS "-Wall")
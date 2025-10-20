cmake_minimum_required(VERSION 3.10)

# Projeto principal: usar C++ e o arquivo main.cpp existente
project(CRUD_CPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CRUD_CPP main.cpp)

cmake_minimum_required(VERSION 3.16)

project(01-01_A_simple_CPP_class LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(01-01_A_simple_CPP_class main.cpp)

include(GNUInstallDirs)
install(TARGETS 01-01_A_simple_CPP_class
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

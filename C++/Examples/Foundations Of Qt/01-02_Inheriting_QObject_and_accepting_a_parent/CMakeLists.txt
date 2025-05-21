cmake_minimum_required(VERSION 3.16)

project(01-02_Inheriting_QObject_and_accepting_a_parent LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(01-02_Inheriting_QObject_and_accepting_a_parent main.cpp)

include(GNUInstallDirs)
install(TARGETS 01-02_Inheriting_QObject_and_accepting_a_parent
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

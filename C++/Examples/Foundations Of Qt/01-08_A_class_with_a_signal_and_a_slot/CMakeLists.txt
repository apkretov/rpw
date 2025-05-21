cmake_minimum_required(VERSION 3.16)

project(01-08_A_class_with_a_signal_and_a_slot LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(01-08_A_class_with_a_signal_and_a_slot
  main.cpp
  MyClass.h
  MyClass.cpp
)
target_link_libraries(01-08_A_class_with_a_signal_and_a_slot Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS 01-08_A_class_with_a_signal_and_a_slot
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

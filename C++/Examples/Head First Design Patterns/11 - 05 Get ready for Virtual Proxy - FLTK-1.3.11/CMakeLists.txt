cmake_minimum_required(VERSION 3.10)
project(AlbumCoverViewer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find FLTK package
find_package(FLTK REQUIRED)

# Add curl library for image downloading
find_package(CURL REQUIRED)

# Add executable
add_executable(AlbumCoverViewer 
    main.cpp
)

# Include directories
target_include_directories(AlbumCoverViewer PRIVATE 
    ${FLTK_INCLUDE_DIR}
    ${CURL_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(AlbumCoverViewer PRIVATE 
    ${FLTK_LIBRARIES}
    ${CURL_LIBRARIES}
)

# Copy FLTK DLLs to output directory
if(WIN32)
    add_custom_command(TARGET AlbumCoverViewer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:fltk::fltk>
        $<TARGET_FILE:fltk::images>
        $<TARGET_FILE_DIR:AlbumCoverViewer>)
endif()
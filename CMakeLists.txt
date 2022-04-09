cmake_minimum_required(VERSION 3.14)
project(Computational_Geometry)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        src/main.cpp
)

set(HEADER_FILES

)

set(SFML_DIR "C:/development_tools/SFML-2.5.1/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "C:/development_tools/SFML-2.5.1/include/")
link_directories("C:/development_tools/SFML-2.5.1/lib/")


set(YOUR_DIRECTORY "./")
add_executable(Computational_Geometry ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(Computational_Geometry PRIVATE ${YOUR_DIRECTORY}/include/)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Computational_Geometry sfml-graphics-d sfml-window-d sfml-system-d)
endif()
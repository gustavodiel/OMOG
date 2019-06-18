cmake_minimum_required(VERSION 3.0)

project(Hermite)

set(CMAKE_CXX_STANDARD 17)

# If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "D:/Windows/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

add_executable(Hermite src/main.cpp src/Application.cpp src/Hermite.cpp src/Point.cpp src/NURBPoint.cpp src/Tangent.cpp src/NURBS.cpp src/CurveJoin.cpp)

set(Hermite "-O2")

target_link_libraries(Hermite sfml-graphics sfml-window sfml-system pthread)

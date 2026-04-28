
cmake_minimum_required(VERSION 3.20)

set(VCPKG_TARGET_TRIPLET "x64-windows")
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(MagneticSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenCV REQUIRED)


add_executable(MAGNETIC_SIM
    src/main.cpp

)

target_link_libraries(MAGNETIC_SIM
    PRIVATE
    glfw
    glad::glad
    ${OpenCV_LIBS}
)
file(GLOB SHADERS "shaders/*.glsl") 

target_include_directories(MAGNETIC_SIM PRIVATE include)

foreach(shader ${SHADERS})
    configure_file(${shader} ${CMAKE_BINARY_DIR}/shaders COPYONLY)
endforeach()
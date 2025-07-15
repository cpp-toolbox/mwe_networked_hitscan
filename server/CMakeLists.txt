cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "src/*.cpp")
# Add the main executable
add_executable(${PROJECT_NAME} ${SOURCES})

add_definitions(-DJPH_DEBUG_RENDERER)

find_package(glm)
find_package(Jolt)
find_package(enet)
find_package(fmt)
target_link_libraries(${PROJECT_NAME} glm::glm Jolt::Jolt enet::enet fmt::fmt)

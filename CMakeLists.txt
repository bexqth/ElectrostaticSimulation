cmake_minimum_required(VERSION 3.22)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
project(ElectrostaticSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(sfml)

file(GLOB SOURCE_FILES *.cpp)

add_executable(electrostatic_app ${SOURCE_FILES})

target_link_libraries(electrostatic_app sfml-graphics sfml-window sfml-system)
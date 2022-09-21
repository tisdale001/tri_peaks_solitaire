# Your CMakeLists.txt for the triPeaks project
cmake_minimum_required(VERSION 3.10)

project(
    triPeaks
    VERSION 1.0
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)


include_directories("./include/")

# link_directories("/usr/lib/x86_64-linux-gnu/")

add_executable(triPeaks ./src/ModelTriPeaks.cpp ./src/ViewTriPeaks.cpp ./src/ControllerTriPeaks.cpp 
./src/Card.cpp ./src/Deck.cpp ./src/Node.cpp ./src/DrawCard.cpp ./src/CardFromGraph.cpp ./src/AnimationWrapper.cpp
./src/Main.cpp)

target_compile_options(triPeaks PRIVATE -Wall -Wextra -Wpedantic)

target_link_libraries(triPeaks sfml-graphics sfml-window sfml-system)
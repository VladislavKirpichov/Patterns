cmake_minimum_required(VERSION 3.22)
project(patterns)

set(CMAKE_CXX_STANDARD 20)
ADD_COMPILE_OPTIONS("-fconcepts")

add_executable(strategy Strategy.cpp)
add_executable(decorator Decorator.cpp Bridge.cpp Visitor.cpp Builder.cpp)
add_executable(factory_method FactoryMethod.cpp)
add_executable(bridge Bridge.cpp)
add_executable(visitor Visitor.cpp)
add_executable(builder Builder.cpp)
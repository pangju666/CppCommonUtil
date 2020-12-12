cmake_minimum_required(VERSION 3.15)
project(CommonUtil VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX d)

file(GLOB headers *.h)
file(GLOB sources *.cpp)

add_library(CommonUtil ${sources} ${headers})

install(TARGETS CommonUtil DESTINATION lib)
install(FILES CommonUtil.h DESTINATION include)

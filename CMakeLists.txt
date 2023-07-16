# cmake to compile thread.cpp into python library

cmake_minimum_required(VERSION 3.12)
project(my_python_lib CXX)

#find_package(PythonLibs 2.7 PATHS "D:\\Python27" REQUIRED)
include_directories("D:\\Python27\\include")

set(SOURCES thread.cpp)

add_library(my_python_lib SHARED ${SOURCES})
#target_compile_definitions(my_python_lib PRIVATE MS_NO_COREDLL)
target_link_libraries(my_python_lib "D:\\Python27\\libs\\python27.lib" "D:\\Python27\\libs\\libpython27.a" "D:\\Python27\\libs\\_ctypes.lib")
# set target name to my_python_lib.pyd
set_target_properties(my_python_lib PROPERTIES SUFFIX ".pyd")

cmake_minimum_required(VERSION 2.8)

project(pgback)

if(APPLE)
# links python2.7.dylib to a specific version - avoids linking to /usr/lib
set(CMAKE_PREFIX_PATH /System/Library/Frameworks/Python.framework/Versions/2.7/lib/ ${CMAKE_PREFIX_PATH}) 
include_directories("/System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7/")
link_directories("/System/Library/Frameworks/Python.framework/Versions/2.7/lib/")
endif(APPLE)

if(UNIX)
include_directories("/usr/include/python2.7/")
endif(UNIX)

include_directories("./qsdk")

set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_C_FLAGS           "${CMAKE_CXX_FLAGS} -O0 -ggdb")
set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_CXX_FLAGS} -O0 -ggdb")
set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_CXX_FLAGS} -O0 -ggdb")
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -O0 -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O0 -ggdb")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(CMAKE_EXE_LINKER_FLAGS -Wl,-map,map.map)

add_library(
    pgback STATIC
    qsdk/qsdk_if.c
    qsdk/util.c
    
    qsdk/QSDK_Property.cpp
    qsdk/QSDK_Device.cpp
    qsdk/QSDK_PropMgr.cpp
    qsdk/QSDK_DevMgr.cpp
    qsdk/QSDK_LibLoader.cpp
    qsdk/QSDK_VDev.cpp
    qsdk/QSDK_RDev.cpp
    qsdk/QSDK_PyLoader.cpp
    qsdk/QSDK_PyInterface.cpp
    qsdk/QSDK_SOLoader.cpp
    main.cpp
    )

#target_link_libraries(pgback python2.7 dl pthread)

install(TARGETS pgback DESTINATION bin)

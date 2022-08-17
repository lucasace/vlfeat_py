cmake_minimum_required(VERSION 3.14)

project(vlfeat.py)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(FetchContent)

set(VLFEAT_FOUND FALSE)

set(VLFEAT_ROOT "${vlfeat_SOURCE_DIR}")

find_package(vlFeat)
if(NOT VLFEAT_FOUND)
    message(STATUS "Couldnt Find vlfeat, Installing Vlfeat")
    include(InstallvlFeat)
    message(STATUS "VLFEAT_ROOT: ${VLFEAT_ROOT}")

    if(NOT VLFEAT_FOUND)
        message(FATAL_ERROR "Could not find vlFeat even after Installing, For more information visit https://www.vlfeat.org")
        return()
    else()
        message(STATUS "Found vlFeat") 
    endif()

endif()

find_package(Python 3.8 REQUIRED
  COMPONENTS NumPy)

if(NOT Python_FOUND)
    message(FATAL_ERROR "Could not find Python")
    return()
endif()

find_package(PythonLibs REQUIRED)

if(NOT PythonLibs_FOUND)
    message(FATAL_ERROR "Could not find PythonLibs")
    return()
endif()

FetchContent_Declare(
    pybind11
    URL https://github.com/pybind/pybind11/archive/v2.3.0.tar.gz
    )

FetchContent_GetProperties(pybind11)

if(NOT pybind11_POPULATED)
    FetchContent_Populate(pybind11)
    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
endif()


find_package(Eigen3 REQUIRED)


set(target "vlfeat_py")

pybind11_add_module(${target} MODULE
    source/vlfeat_py.h
    source/vlfeat_py.cpp
    source/sift/sift.cpp
    source/sift/dsift.cpp
    source/mser/mser.cpp
)


target_include_directories(${target}

    PRIVATE
        ${VLFEAT_INCLUDE_DIRS}
        ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(${target}
    PRIVATE
        ${VLFEAT_LIBRARIES}
        ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES} 
        Python::NumPy
        Eigen3::Eigen
)

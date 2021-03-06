#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

cmake_minimum_required(VERSION 3.8)
project(cozmonaut CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include(GetGitRevisionDescription)

find_package(PythonInterp 3.7 REQUIRED)
find_package(PythonLibs 3.7 REQUIRED)

add_subdirectory(third_party/pybind11)

get_git_head_revision(GIT_REFSPEC GIT_HASH)

set(cozmo_SRC_FILES
        src/global.cpp
        src/main.cpp
        )

set(cozmo_VERSION_MAJOR 0)
set(cozmo_VERSION_MINOR 1)
set(cozmo_VERSION_PATCH 0)

add_executable(cozmo ${cozmo_SRC_FILES})
set_target_properties(cozmo PROPERTIES CXX_STANDARD 17)
target_include_directories(cozmo PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(cozmo PRIVATE ${PYTHON_LIBRARIES} pybind11::pybind11)

target_compile_definitions(cozmo PRIVATE
        -D__version_major=${cozmo_VERSION_MAJOR}
        -D__version_minor=${cozmo_VERSION_MINOR}
        -D__version_patch=${cozmo_VERSION_PATCH}
        -D__git_hash=${GIT_HASH}
        -D__git_hash_str="${GIT_HASH}"
        -D__git_refspec=${GIT_REFSPEC}
        -D__git_refspec_str="${GIT_REFSPEC}"
        )

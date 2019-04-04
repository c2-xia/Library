cmake_minimum_required (VERSION 3.1) 
set (CMAKE_CPP_STANDARD 15)
set (CMAKE_C_STANDARD 15)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Od")
project (Binary2Text)

function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

function(my_add_executable)
    foreach(_source IN ITEMS ${ARGN})
        assign_source_group(${_source})
    endforeach()
    add_executable(${ARGV})
endfunction(my_add_executable)

function(my_add_library)
    foreach(_source IN ITEMS ${ARGN})
        assign_source_group(${_source})
    endforeach()
    add_library(${ARGV})
endfunction(my_add_library)

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
source_group("Include" FILES ${CURRENT_HEADERS}) 

ADD_DEFINITIONS(
-D__STDC_LIMIT_MACROS
-D__STDC_FORMAT_MACROS
-D__STDC_CONSTANT_MACROS
-D_HAS_ITERATOR_DEBUGGING=0
-D_DEBUG
-DWIN32
-D_WIN32
-D_HAS_EXCEPTIONS=0
-D_HAS_ITERATOR_DEBUGGING=0
-D_SCL_SECURE=0
-D_SECURE_SCL=0
-D_SCL_SECURE_NO_WARNINGS
-D_CRT_SECURE_NO_WARNINGS
-D_CRT_SECURE_NO_DEPRECATE
 /Zi
)

include_directories ("${PROJECT_SOURCE_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/Yaml")
add_subdirectory (Yaml)

include_directories ("${PROJECT_SOURCE_DIR}/3rd/gdtoa")
add_subdirectory (3rd/gdtoa)


my_add_executable(Binary2Text
_demo/main.cpp
_demo/relationdata2Text/Relationdata2Text.cpp
_demo/simpledata2Text/Simpledata2Text.cpp
ReaderWriter/extraFunction.cpp
ReaderWriter/Yaml/YamlWriter.cpp
_demo/relationdata2Text/New.cpp
${CURRENT_HEADERS}
)

target_link_libraries(Binary2Text
gdtoa
Yaml
)



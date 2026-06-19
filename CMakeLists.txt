cmake_minimum_required(VERSION 3.16)
project(krow LANGUAGES CXX)

find_package(Curses REQUIRED)

add_library(krow
    src/K10-K10/input/cursor.cc
    src/K10-K10/input/keyboard.cc
    src/K10-K10/utils/base.cc
    src/K10-K10/utils/string_helper.cc
    src/K10-K10/style/color.cc
    src/K10-K10/style/style.cc
    src/K10-K10/app/app.cc
    src/K10-K10/core/drawObj.cc
    src/K10-K10/core/render.cc
    src/K10-K10/core/screen.cc
    src/K10-K10/obj/block.cc
    src/K10-K10/obj/list.cc
    src/K10-K10/obj/text.cc
    src/K10-K10/obj/input.cc
)

target_compile_features(krow PUBLIC cxx_std_20)

target_include_directories(krow PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_include_directories(krow PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(krow PUBLIC
    ${CURSES_LIBRARIES}
)

add_library(K10-K10::krow ALIAS krow)

option(BUILD_TESTS "Build automated tests" OFF)

option(BUILD_SANDBOX "Build development sandbox" OFF)

if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

if (BUILD_SANDBOX)
  add_subdirectory(sandbox)
endif()

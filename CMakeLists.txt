cmake_minimum_required(VERSION 3.20)
project(dsa_refresher CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

add_compile_options(-Wall -Wextra -Wno-unused-parameter)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address,undefined)
endif()

# doctest's main(), compiled once and linked into every test binary.
add_library(dsa_test_main STATIC common/test_main.cpp)
target_include_directories(dsa_test_main PUBLIC third_party/doctest common)

add_executable(common_tests tests/common_test.cpp)
target_link_libraries(common_tests PRIVATE dsa_test_main)

# Each topics/NN_topic/<name>/test.cpp becomes ex_NN_<name> (built against the
# learner's header) and, if a reference exists, sol_NN_<name> (built against
# solutions/). Tests include the header with <angle brackets>, so only the -I
# path decides which one is used.
file(GLOB EXERCISE_TESTS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/topics/*/*/test.cpp)
file(GLOB SOLUTION_HEADERS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/solutions/*/*/*.hpp)

foreach(test_cpp IN LISTS EXERCISE_TESTS)
  get_filename_component(ex_dir ${test_cpp} DIRECTORY)
  get_filename_component(ex_name ${ex_dir} NAME)
  get_filename_component(topic_dir ${ex_dir} DIRECTORY)
  get_filename_component(topic_name ${topic_dir} NAME)
  string(SUBSTRING ${topic_name} 0 2 topic_num)

  add_executable(ex_${topic_num}_${ex_name} ${test_cpp})
  target_include_directories(ex_${topic_num}_${ex_name} PRIVATE ${ex_dir})
  target_link_libraries(ex_${topic_num}_${ex_name} PRIVATE dsa_test_main)

  set(sol_dir ${CMAKE_SOURCE_DIR}/solutions/${topic_name}/${ex_name})
  if(EXISTS ${sol_dir}/${ex_name}.hpp)
    add_executable(sol_${topic_num}_${ex_name} ${test_cpp})
    target_include_directories(sol_${topic_num}_${ex_name} PRIVATE ${sol_dir})
    target_link_libraries(sol_${topic_num}_${ex_name} PRIVATE dsa_test_main)
  endif()
endforeach()

cmake_minimum_required(VERSION 3.0)

project(psp2nidcompat C)

set(CMAKE_C_COMPILE_FEATURES "${CMAKE_C_FLAGS} -Wunused-result -Wl,-q -Wall -O3 -fno-inline -fno-builtin")

include_directories(
 ./include/
)

add_executable(${PROJECT_NAME}
  src/main.c
  src/nidcompat.c
  src/nidcompat_utils.c
  src/fs_list.c
)

target_link_libraries(${PROJECT_NAME}
  crypto
  z
)

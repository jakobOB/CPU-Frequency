cmake_minimum_required(VERSION 3.5)

project(A6_C
  LANGUAGES C ASM)


add_executable(A6_cpu_frequency
  cpu_frequency.c
  )
target_compile_options(A6_cpu_frequency PRIVATE
  -m64 -O0 -Wall -Wextra -mno-red-zone)

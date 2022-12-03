# Solution day 3
add_executable(day3 solution-day3.c)

find_package(OpenMP)
if(OpenMP_C_FOUND)
    target_link_libraries(day3 PUBLIC OpenMP::OpenMP_C)
endif()
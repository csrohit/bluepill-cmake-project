# specify name of library
add_library(gpio "")

# add sources for library
target_sources(gpio
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/gpio.cpp
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/gpio.hpp
)

# add this path to include directories for the target
target_include_directories(gpio
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_SOURCE_DIR}/include
)

# add flags for compiler
target_compile_options(gpio
    PRIVATE
        ${CPU_PARAMETERS}
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wdouble-promotion
        -Wformat=2 -Wformat-truncation
        -Wundef
        -fno-common
        -Wno-unused-parameter
        $<$<COMPILE_LANGUAGE:CXX>:
            -Wconversion # STM libraries!
            -Wno-volatile
            # -Wold-style-cast
            # -Wuseless-cast
            -Wsuggest-override>
        $<$<CONFIG:Debug>:-Og -g3 -ggdb>
        $<$<CONFIG:Release>:-Og -g0>
)


# STM32 Minimal CMake project for C/C++ projects
cmake_minimum_required(VERSION 3.22)

# Set project name
project(blink LANGUAGES CXX C ASM)
set(EXECUTABLE ${CMAKE_PROJECT_NAME})


# Set microcontroller information
set(MCU_FAMILY STM32F1xx)
set(MCU_MODEL STM32F103xB)
set(CPU_PARAMETERS
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft
)

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/src/startup_stm32f103c8tx.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F103C8TX_FLASH.ld)


# enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# add directories to look for header files
set(PROJECT_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)


# add source files for project
add_executable(${EXECUTABLE}
    src/main.cpp
    src/system_stm32f1xx.c
    ${STARTUP_SCRIPT}
)

# add directories for searching libraries
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/gpio)

# link libraries with the executable
target_link_libraries(${CMAKE_PROJECT_NAME}
    PUBLIC
    gpio
)

# add definitions to be passed to compiler
target_compile_definitions(${EXECUTABLE}
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        ${MCU_MODEL}
)

# add include directories 
target_include_directories(${EXECUTABLE} PRIVATE
    ${PROJECT_INCLUDE_DIRECTORIES})
    
# add flags for compiler
target_compile_options(${EXECUTABLE}
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

# add flags for linker
target_link_options(${EXECUTABLE} 
    PRIVATE
        -T${MCU_LINKER_SCRIPT}
        ${CPU_PARAMETERS}
        -Wl,-Map=${CMAKE_PROJECT_NAME}.map
        --specs=nosys.specs
        -Wl,--start-group
        -lc
        -lm
        -lstdc++
        -Wl,--end-group
        -Wl,--print-memory-usage
)

# The last command can take a couple of seconds on larger project, usefull for debugging
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin
)

# add target for flashing the micro-controller 
add_custom_target(flash
    COMMAND openocd -d2 -f interface/stlink.cfg -c \"transport select hla_swd\" -f target/stm32f1x.cfg -c \"program {${EXECUTABLE}.elf} verify reset\; shutdown\;\"
)


set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

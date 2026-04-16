cmake_minimum_required(VERSION 3.20)

# Thank you Claude AI for having helped with the CMake setup :)

# Must set toolchain BEFORE project()
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/wii_toolchain.cmake"
        CACHE STRING "Wii cross-compilation toolchain")

project(Template CXX C ASM)

# -----------------------------------------------------------------------
# devkitPro paths
# -----------------------------------------------------------------------
set(DEVKITPRO $ENV{DEVKITPRO})
set(DEVKITPPC $ENV{DEVKITPPC})
set(LIBOGC_DIR  ${DEVKITPRO}/libogc)
set(PORTLIBS    ${DEVKITPRO}/portlibs/wii)

# -----------------------------------------------------------------------
# Compiler flags (Wii / Broadway CPU)
# -----------------------------------------------------------------------
# Use add_compile_options (not CMAKE_CXX_FLAGS_INIT) so flags are always
# applied, even when CMake re-uses a cached build directory.
add_compile_options(
        -DGEKKO          # platform guard required by gctypes.h / libogc headers
        -mrvl            # Wii/RVL target ABI
        -mcpu=750        # Broadway CPU (PowerPC 750CL)
        -meabi           # Embedded ABI
        -mhard-float     # hardware FPU
        -O2
        -Wall
)
# C++-only flags (appended after the shared ones above)
add_compile_options(
        $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
)

# -----------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------
file(GLOB_RECURSE SOURCES src/*.cpp src/*.c)

add_executable(${PROJECT_NAME}.elf ${SOURCES})
set_target_properties(${PROJECT_NAME}.elf PROPERTIES
        OUTPUT_NAME "boot.elf"
)

set_target_properties(${PROJECT_NAME}.elf PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

# -----------------------------------------------------------------------
# Include dirs
# -----------------------------------------------------------------------
target_include_directories(${PROJECT_NAME}.elf PRIVATE
        ${LIBOGC_DIR}/include
        ${PORTLIBS}/include
        ${CMAKE_SOURCE_DIR}/src
)

# -----------------------------------------------------------------------
# Linker flags & libraries
# -----------------------------------------------------------------------
# libogc ships a linker script for the Wii
set(WII_LDSCRIPT "${DEVKITPPC}/powerpc-eabi/lib/rvl.ld")

target_link_options(${PROJECT_NAME}.elf PRIVATE
        -L${LIBOGC_DIR}/lib/wii
        -L${PORTLIBS}/lib
        -T${WII_LDSCRIPT}
        -mrvl
        -meabi
        -mhard-float
)

target_link_libraries(${PROJECT_NAME}.elf
        wiiuse
        bte
        -Wl,--start-group
        ogc
        fat
        -Wl,--end-group
        m
)

# -----------------------------------------------------------------------
# Post-build: .elf → .dol  (the format the Homebrew Channel loads)
# -----------------------------------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND $ENV{DEVKITPRO}/tools/bin/elf2dol
        ${CMAKE_BINARY_DIR}/boot.elf
        ${CMAKE_BINARY_DIR}/boot.dol
        COMMENT "Converting ELF → DOL"
)
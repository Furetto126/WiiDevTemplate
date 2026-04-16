# cmake/wii_toolchain.cmake
# Cross-compilation toolchain for Nintendo Wii (libogc / devkitPPC)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR powerpc)

# --- Locate devkitPro ---
if(NOT DEFINED ENV{DEVKITPRO})
    message(FATAL_ERROR "DEVKITPRO environment variable not set. "
            "Install devkitPro and export DEVKITPRO=/opt/devkitpro")
endif()

set(DEVKITPRO $ENV{DEVKITPRO})
set(DEVKITPPC ${DEVKITPRO}/devkitPPC)

# --- Compilers ---
set(CMAKE_C_COMPILER   ${DEVKITPPC}/bin/powerpc-eabi-gcc)
set(CMAKE_CXX_COMPILER ${DEVKITPPC}/bin/powerpc-eabi-g++)
set(CMAKE_ASM_COMPILER ${DEVKITPPC}/bin/powerpc-eabi-as)
set(CMAKE_AR           ${DEVKITPPC}/bin/powerpc-eabi-ar CACHE FILEPATH "Archiver")
set(CMAKE_LINKER       ${DEVKITPPC}/bin/powerpc-eabi-ld)
set(CMAKE_OBJCOPY      ${DEVKITPPC}/bin/powerpc-eabi-objcopy)

# Tell CMake not to try to run test executables (they're PowerPC)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# --- System roots (prevents CMake from using host headers) ---
set(CMAKE_FIND_ROOT_PATH ${DEVKITPPC} ${DEVKITPRO}/portlibs/wii ${DEVKITPRO}/libogc)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
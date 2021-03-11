cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

#if(NOT MINGW AND NOT WIN32 AND NOT MINGW64)
#    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
#    set(CMAKE_CXX_FLAGS_DEBUG "-g")
#    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
#endif()

project (libdsp VERSION 1.0)

if(MSVC)
    # Needed for M_PI macro
    add_definitions(-D_USE_MATH_DEFINES)
    # Export all symbols in DLL - Could use __declspec(dllexport) if need to be
    # more selective
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

file(GLOB_RECURSE DSP_CPPS src/*.cpp)

add_library(dsp SHARED ${DSP_CPPS})

file(GLOB_RECURSE DSP_HS src/*.h)

include(GNUInstallDirs)
install(TARGETS dsp LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${DSP_HS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/dsp)
install(DIRECTORY src/math DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/dsp)

cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project (libdsp VERSION 1.0)

file(GLOB_RECURSE DSP_CPPS src/*.cpp)

add_library(dsp SHARED ${DSP_CPPS})

file(GLOB_RECURSE DSP_HS src/*.h)

include(GNUInstallDirs)
install(TARGETS dsp LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${DSP_HS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/dsp)
install(DIRECTORY src/math DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/dsp)

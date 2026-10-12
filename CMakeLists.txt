cmake_minimum_required(VERSION 3.25)
project(IBM_Legacy_Virtual_Hardware VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_library(ibmlegacy
    src/tape/tape_image.cpp
    src/machines/ibm1401.cpp
    src/machines/system360.cpp
    src/machines/ebcdic.cpp
    src/machine_profiles.cpp
    src/devices/tape_drive.cpp
    src/devices/device_bus.cpp
    src/devices/ibm1402_reader.cpp
    src/devices/ibm1403_printer.cpp
    src/devices/ibm2540_reader_punch.cpp
    src/devices/tape_models.cpp
    src/devices/card_deck.cpp
    src/devices/line_printer.cpp
    src/devices/channel.cpp
    src/runtime_config.cpp
    src/hex_loader.cpp
    src/binary_loader.cpp
    src/cpu/system360_cpu.cpp
    src/cpu/system360_alu.cpp
    src/cpu/system360_decoder.cpp
    src/trace_logger.cpp
    src/cpu/ibm1401_cpu.cpp
    src/assembler/lexer.cpp
    src/assembler/encoder.cpp
)
target_include_directories(ibmlegacy PUBLIC include)

add_library(ibmfortran STATIC
    src/fortran/fortran_compiler.cpp
    src/fortran/source_reader.cpp
    src/fortran/diagnostic.cpp
    src/fortran/lexer.cpp
    src/fortran/symbol_table.cpp
    src/fortran/intrinsics.cpp
    src/fortran/runtime_io.cpp
    src/fortran/runtime_math.cpp
    src/fortran/format_descriptor.cpp
    src/fortran/expression.cpp
    src/fortran/array.cpp
    src/fortran/parser.cpp
    src/fortran/app.cpp
    src/fortran/tool.cpp
)
add_library(ibmlegacy::fortran ALIAS ibmfortran)
target_include_directories(ibmfortran PUBLIC include)
if(MSVC)
  target_compile_options(ibmfortran PRIVATE /W4 /permissive-)
else()
  target_compile_options(ibmfortran PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()
if(MSVC)
  target_compile_options(ibmlegacy PRIVATE /W4 /permissive-)
else()
  target_compile_options(ibmlegacy PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()
add_executable(ibm-legacy src/main.cpp)
target_link_libraries(ibm-legacy PRIVATE ibmlegacy)
add_executable(ibm-fortran src/fortran_main.cpp)
target_link_libraries(ibm-fortran PRIVATE ibmfortran)
add_executable(ibm-as src/assembler_main.cpp)
target_link_libraries(ibm-as PRIVATE ibmlegacy)
add_executable(ibm-fortran-app src/fortran_app_main.cpp)
target_link_libraries(ibm-fortran-app PRIVATE ibmfortran)
add_executable(ibm-fortran-tool src/fortran_tool_main.cpp)
target_link_libraries(ibm-fortran-tool PRIVATE ibmfortran)
include(CTest)
if(BUILD_TESTING)
  add_executable(ibmlegacy-tests tests/test_main.cpp)
  target_link_libraries(ibmlegacy-tests PRIVATE ibmlegacy ibmfortran)
  add_test(NAME ibmlegacy-tests COMMAND ibmlegacy-tests)
endif()

include(GNUInstallDirs)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/fortran DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
install(TARGETS ibmlegacy ibmfortran ibm-legacy ibm-fortran ibm-as
                ibm-fortran-app ibm-fortran-tool
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY resources/fortran DESTINATION ${CMAKE_INSTALL_DATADIR}/ibmlegacy)

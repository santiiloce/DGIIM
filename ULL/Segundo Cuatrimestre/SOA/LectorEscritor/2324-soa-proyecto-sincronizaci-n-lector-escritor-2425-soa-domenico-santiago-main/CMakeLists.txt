cmake_minimum_required(VERSION 3.14)

project(lector_escritor_base LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(lector_escritor_base
  main.cpp
  buffer.h buffer.cpp
  reader.h reader.cpp
  writer.h writer.cpp
)
target_link_libraries(lector_escritor_base Qt${QT_VERSION_MAJOR}::Core)

# Copiar el archivo README.md al directorio de compilación
configure_file(${CMAKE_SOURCE_DIR}/README.md ${CMAKE_BINARY_DIR}/README.md COPYONLY)

include(GNUInstallDirs)
install(TARGETS lector_escritor_base
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

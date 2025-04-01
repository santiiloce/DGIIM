cmake_minimum_required(VERSION 3.14)

project(productor_consumidor_base LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# Copiar el archivo README.md al directorio de compilación
configure_file(${CMAKE_SOURCE_DIR}/README.md ${CMAKE_BINARY_DIR}/README.md COPYONLY)

add_executable(productor_consumidor_base
  main.cpp
  buffer.h buffer.cpp
  consumer.h consumer.cpp
  producer.h producer.cpp
)

target_link_libraries(productor_consumidor_base Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS productor_consumidor_base
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

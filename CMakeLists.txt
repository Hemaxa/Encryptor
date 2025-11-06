cmake_minimum_required(VERSION 3.21)
project(Encryptor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(Encryptor WIN32 MACOSX_BUNDLE)

set_target_properties(Encryptor PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in")

target_sources (Encryptor PRIVATE
    ${SRC_DIR}/resources.qrc

    ${SRC_DIR}/Main.cpp

    ${SRC_DIR}/Window/MainWindow.h
    ${SRC_DIR}/Window/MainWindow.cpp

    ${SRC_DIR}/BaseEncrMethod.h

    ${SRC_DIR}/Methods/EncrMethod1.h
    ${SRC_DIR}/Methods/EncrMethod1.cpp
    ${SRC_DIR}/Methods/EncrMethod2.h
    ${SRC_DIR}/Methods/EncrMethod2.cpp
    ${SRC_DIR}/Methods/EncrMethod3.h
    ${SRC_DIR}/Methods/EncrMethod3.cpp
    ${SRC_DIR}/Methods/EncrMethod4.h
    ${SRC_DIR}/Methods/EncrMethod4.cpp
    ${SRC_DIR}/Methods/EncrMethod5.h
    ${SRC_DIR}/Methods/EncrMethod5.cpp
)

target_include_directories(Encryptor PRIVATE
    ${SRC_DIR}
    ${SRC_DIR}/Window
    ${SRC_DIR}/Methods
)

target_link_libraries(Encryptor PRIVATE
    Qt::Core
    Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Encryptor

BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_standard_project_setup()

qt_generate_deploy_app_script(
    TARGET Encryptor
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})

cmake_minimum_required(VERSION 3.1)

project(Qt-csv-editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

option(UPDATE_TRANSLATIONS "Update source translation (files translations/*.ts)." ON)

set(TS_FILES
    Qt-csv-editor_en_EN.ts)

set(PROJECT_SOURCES main.cpp
    mainwindow.cpp
    mdichild.cpp
    csvio.cpp
    combodelegate.cpp
    intdelegate.cpp
    booldelegate.cpp)

set(PROJECT_HEADERS
    mainwindow.h
    mdichild.h
    csvio.h
    combodelegate.h
    intdelegate.h
    booldelegate.h)

set(PROJECT_FORMS
    mainwindow.ui
    mdichild.ui)

set(TRANSLATABLES ${PROJECT_FORMS} ${PROJECT_HEADERS})

if(UPDATE_TRANSLATIONS)
    message(STATUS "UPDATE_TRANSLATIONS option is set.")
    qt_create_translation(QM_FILES ${TRANSLATABLES} ${TS_FILES})
    #qt_add_lupdate(Qt-csv-editor ${TS_FILES})
else()
    message(STATUS "UPDATE_TRANSLATIONS option is NOT set.")
    qt_add_translation(QM_FILES ${TS_FILES})
    #qt_add_lrelease(Qt-csv-editor ${TS_FILES} QM_FILES_OUTPUT_VARIABLE QM_FILES)
endif()
message(STATUS "QM files: " ${QM_FILES})

add_custom_target(translations DEPENDS ${QM_FILES})
set_property(DIRECTORY PROPERTY CLEAN_NO_CUSTOM TRUE)

qt_wrap_cpp(MOC_WRAPPERS ${PROJECT_HEADERS})

add_executable(Qt-csv-editor WIN32
    ${PROJECT_SOURCES}
    ${MOC_WRAPPERS}
    ${PROJECT_FORMS})

add_dependencies(Qt-csv-editor translations)

target_link_libraries(Qt-csv-editor PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(Qt-csv-editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Qt-csv-editor PRIVATE Qt${QT_VERSION_MAJOR}::Gui)

#installation
include(DeployQt4)
set(CMAKE_INSTALL_PREFIX "D:/Programs/Qt-csv-editor/" )
get_property(LIB_QTCORE_PATH TARGET Qt6::Core PROPERTY IMPORTED_LOCATION_RELEASE)
get_property(LIB_QTWIDGETS_PATH TARGET Qt6::Widgets PROPERTY IMPORTED_LOCATION_RELEASE)
get_property(LIB_QTGUI_PATH TARGET Qt6::Gui PROPERTY IMPORTED_LOCATION_RELEASE)

get_filename_component(QT_LIBRARY_DIR "${LIB_QTCORE_PATH}" DIRECTORY)
get_filename_component(QT_PATH "${LIB_QTCORE_PATH}" PATH)
get_filename_component(QT_PATH "${QT_PATH}" PATH)

message(STATUS "Qt path" ${QT_PATH})
install(DIRECTORY "${QT_PATH}/plugins/platforms" DESTINATION bin)
install(TARGETS Qt-csv-editor RUNTIME DESTINATION bin)
install(FILES ${QM_FILES} DESTINATION translations)

set(EXE_PATH bin/Qt-csv-editor${CMAKE_EXECUTABLE_SUFFIX})

install(FILES "${LIB_QTCORE_PATH}" DESTINATION bin)
install(FILES "${LIB_QTWIDGETS_PATH}" DESTINATION bin)
install(FILES "${LIB_QTGUI_PATH}" DESTINATION bin)

message(STATUS "Installing to " ${CMAKE_INSTALL_PREFIX})

install_qt4_executable(
    "${EXE_PATH}"     #исполняемый файл
    ""                  #модули
    ""                  #библиотеки
    ${QT_LIBRARY_DIR} )#каталоги

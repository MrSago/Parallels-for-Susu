set(QT_PREFIX_PATH_CMAKE_FILE ${Parallels-for-Susu_SOURCE_DIR}/qtprefixpath.cmake)

if (NOT DEFINED CMAKE_PREFIX_PATH AND EXISTS ${QT_PREFIX_PATH_CMAKE_FILE})
  include(${QT_PREFIX_PATH_CMAKE_FILE})
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB TARGET_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lab2-sender
        MANUAL_FINALIZATION
        ${TARGET_SOURCES}
    )
endif()

target_include_directories(lab2-sender PRIVATE ${Parallels-for-Susu_SOURCE_DIR})
target_link_libraries(lab2-sender PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(lab2-sender PROPERTIES
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab2-sender)
endif()

find_program(TOOL_WINDEPLOYQT NAMES windeployqt)
add_custom_command(TARGET lab2-sender POST_BUILD
  COMMAND ${TOOL_WINDEPLOYQT}
          $<TARGET_FILE:lab2-sender>
  COMMENT "Running windeployqt..."
)

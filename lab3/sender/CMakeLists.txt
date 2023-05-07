file(GLOB TARGET_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

add_executable(lab3-sender ${TARGET_SOURCES})
target_include_directories(lab3-sender PRIVATE ${Parallels-for-Susu_SOURCE_DIR})
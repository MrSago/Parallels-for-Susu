file(GLOB TARGET_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

add_executable(lab3-reciever ${TARGET_SOURCES})
target_include_directories(lab3-reciever PRIVATE ${Parallels-for-Susu_SOURCE_DIR})
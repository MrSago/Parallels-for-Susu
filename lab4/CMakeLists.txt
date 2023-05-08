find_package(OpenMP REQUIRED)

function(init_target_lab4 TARGET)
  file(GLOB TARGET_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
  )

  add_executable(${TARGET} ${TARGET_SOURCES})
  target_link_libraries(${TARGET} OpenMP::OpenMP_C)
  target_include_directories(${TARGET} PRIVATE
      ${Parallels-for-Susu_SOURCE_DIR}
      OpenMP::OpenMP_C
  )
endfunction(init_target_lab4 TARGET)

add_subdirectory(hello)
add_subdirectory(iam)
add_subdirectory(hiden)
add_subdirectory(reduction)
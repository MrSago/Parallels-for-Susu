find_package(MPI REQUIRED)

function(init_target_lab5 TARGET)
  file(GLOB TARGET_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
  )

  add_executable(${TARGET} ${TARGET_SOURCES})
  target_link_libraries(${TARGET} MPI::MPI_C)
  target_include_directories(${TARGET} PRIVATE
      ${Parallels-for-Susu_SOURCE_DIR}
      MPI::MPI_C
  )
endfunction(init_target_lab5 TARGET)

add_subdirectory(iam)
add_subdirectory(first-second)
add_subdirectory(send)
add_subdirectory(baton)
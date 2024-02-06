# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cpp)
foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cpp" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cpp)
  set_target_properties(${EXAMPLE}
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${Bin_Root}
	ARCHIVE_OUTPUT_DIRECTORY ${Lib_Root}
  )
  target_link_libraries(${EXAMPLE} PRIVATE fmt::fmt)
endforeach()
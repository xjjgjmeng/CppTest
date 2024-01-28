# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cpp)
foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cpp" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cpp)
  # target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach()
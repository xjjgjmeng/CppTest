cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)

set(Bin_Root "${CMAKE_SOURCE_DIR}/Bin")
set(Lib_Root "${CMAKE_SOURCE_DIR}/Lib")

project(CppTest)

# fmt
option(auto_fetch_fmt "auto_fetch_fmt." ON)
if (auto_fetch_fmt)
	include(FetchContent)
	FetchContent_Declare(fmt
		GIT_REPOSITORY https://github.com/fmtlib/fmt.git
		GIT_TAG 10.2.1
		SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/fmt"
	)
	FetchContent_MakeAvailable(fmt)
else()
    add_subdirectory(fmt)
endif()

add_subdirectory(src)
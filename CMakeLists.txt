cmake_minimum_required(VERSION 3.28)
project(lcc LANGUAGES C VERSION 4.2.0)

#
# options
#

if(NOT LCC_HOST_FILE_DEFAULT)
	if(LINUX)
		set(LCC_HOST_FILE_DEFAULT linux.c)
	elseif(WIN32)
		set(LCC_HOST_FILE_DEFAULT win32.c)
	else()
		message(WARNING "Platform is not Linux or Windows - automatically assuming bytecode-only target")
		set(LCC_HOST_FILE_DEFAULT bytecodelcc.c)
	endif()
endif()

set(LCC_HOST_FILE ${LCC_HOST_FILE_DEFAULT} CACHE STRING "Platform host source file")
set_property(CACHE LCC_HOST_FILE PROPERTY STRINGS bytecodelcc.c gcc-solaris.c irix.c linux.c osf.c solaris.c win32.c)

#
# packages
#

find_package(BISON REQUIRED)

#
# preprocessor
#

add_executable(lcc-cpp
	${PROJECT_SOURCE_DIR}/cpp/cpp.c
	${PROJECT_SOURCE_DIR}/cpp/lex.c
	${PROJECT_SOURCE_DIR}/cpp/nlist.c
	${PROJECT_SOURCE_DIR}/cpp/tokens.c
	${PROJECT_SOURCE_DIR}/cpp/macro.c
	${PROJECT_SOURCE_DIR}/cpp/eval.c
	${PROJECT_SOURCE_DIR}/cpp/include.c
	${PROJECT_SOURCE_DIR}/cpp/hideset.c
	${PROJECT_SOURCE_DIR}/cpp/getopt.c
	${PROJECT_SOURCE_DIR}/cpp/unix.c
)

#
# code-generator-generator
#

bison_target(
	lcc-lburg-gram
	${PROJECT_SOURCE_DIR}/lburg/gram.y
	${PROJECT_BINARY_DIR}/gram.c
)

add_executable(lcc-lburg
	${PROJECT_BINARY_DIR}/gram.c
	${PROJECT_SOURCE_DIR}/lburg/lburg.c
)

target_include_directories(lcc-lburg PRIVATE ${PROJECT_SOURCE_DIR}/lburg)

#
# compiler frontend
#

add_executable(lcc
	${PROJECT_SOURCE_DIR}/etc/${LCC_HOST_FILE}
	${PROJECT_SOURCE_DIR}/etc/lcc.c
)

#
# liblcc
#

add_library(liblcc STATIC
	${PROJECT_SOURCE_DIR}/lib/assert.c
	${PROJECT_SOURCE_DIR}/lib/bbexit.c
	${PROJECT_SOURCE_DIR}/lib/yynull.c
)
set_target_properties(liblcc PROPERTIES OUTPUT_NAME lcc)

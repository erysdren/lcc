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
		message(WARNING "Platform is not Linux or Windows - automatically assuming generic target")
		set(LCC_HOST_FILE_DEFAULT generic.c)
	endif()
endif()

set(LCC_HOST_FILE ${LCC_HOST_FILE_DEFAULT} CACHE STRING "Platform host source file")
set_property(CACHE LCC_HOST_FILE PROPERTY STRINGS generic.c gcc-solaris.c irix.c linux.c osf.c solaris.c win32.c)

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

function(lcc_lburg_target input output)
	add_custom_command(
		OUTPUT ${output}
		COMMAND $<TARGET_FILE:lcc-lburg> ${input} ${output}
		COMMAND_EXPAND_LISTS
		VERBATIM
	)
endfunction()

#
# compiler backend
#

lcc_lburg_target(${PROJECT_SOURCE_DIR}/src/alpha.md ${PROJECT_BINARY_DIR}/alpha.c)
lcc_lburg_target(${PROJECT_SOURCE_DIR}/src/dagcheck.md ${PROJECT_BINARY_DIR}/dagcheck.c)
lcc_lburg_target(${PROJECT_SOURCE_DIR}/src/mips.md ${PROJECT_BINARY_DIR}/mips.c)
lcc_lburg_target(${PROJECT_SOURCE_DIR}/src/sparc.md ${PROJECT_BINARY_DIR}/sparc.c)
lcc_lburg_target(${PROJECT_SOURCE_DIR}/src/x86.md ${PROJECT_BINARY_DIR}/x86.c)
lcc_lburg_target(${PROJECT_SOURCE_DIR}/src/x86linux.md ${PROJECT_BINARY_DIR}/x86linux.c)

add_executable(lcc-rcc
	${PROJECT_SOURCE_DIR}/src/alloc.c
	${PROJECT_SOURCE_DIR}/src/bind.c
	${PROJECT_SOURCE_DIR}/src/dag.c
	${PROJECT_SOURCE_DIR}/src/decl.c
	${PROJECT_SOURCE_DIR}/src/enode.c
	${PROJECT_SOURCE_DIR}/src/error.c
	${PROJECT_SOURCE_DIR}/src/expr.c
	${PROJECT_SOURCE_DIR}/src/event.c
	${PROJECT_SOURCE_DIR}/src/init.c
	${PROJECT_SOURCE_DIR}/src/inits.c
	${PROJECT_SOURCE_DIR}/src/input.c
	${PROJECT_SOURCE_DIR}/src/lex.c
	${PROJECT_SOURCE_DIR}/src/list.c
	${PROJECT_SOURCE_DIR}/src/main.c
	${PROJECT_SOURCE_DIR}/src/output.c
	${PROJECT_SOURCE_DIR}/src/prof.c
	${PROJECT_SOURCE_DIR}/src/profio.c
	${PROJECT_SOURCE_DIR}/src/simp.c
	${PROJECT_SOURCE_DIR}/src/stmt.c
	${PROJECT_SOURCE_DIR}/src/string.c
	${PROJECT_SOURCE_DIR}/src/sym.c
	${PROJECT_SOURCE_DIR}/src/trace.c
	${PROJECT_SOURCE_DIR}/src/tree.c
	${PROJECT_SOURCE_DIR}/src/types.c
	${PROJECT_SOURCE_DIR}/src/null.c
	${PROJECT_SOURCE_DIR}/src/symbolic.c
	${PROJECT_SOURCE_DIR}/src/gen.c
	${PROJECT_SOURCE_DIR}/src/bytecode.c
	${PROJECT_SOURCE_DIR}/src/stab.c

	${PROJECT_BINARY_DIR}/alpha.c
	${PROJECT_BINARY_DIR}/dagcheck.c
	${PROJECT_BINARY_DIR}/mips.c
	${PROJECT_BINARY_DIR}/sparc.c
	${PROJECT_BINARY_DIR}/x86.c
	${PROJECT_BINARY_DIR}/x86linux.c
)
target_include_directories(lcc-rcc PRIVATE ${PROJECT_SOURCE_DIR}/src)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	target_compile_options(lcc-rcc PRIVATE -Wno-abi) # shut up gcc
endif()

#
# compiler frontend
#

add_executable(lcc
	${PROJECT_SOURCE_DIR}/etc/${LCC_HOST_FILE}
	${PROJECT_SOURCE_DIR}/etc/lcc.c
)

#
# bprint
#

add_executable(bprint
	${PROJECT_SOURCE_DIR}/etc/bprint.c
)
target_include_directories(bprint PRIVATE ${PROJECT_SOURCE_DIR}/src)

#
# liblcc
#

add_library(liblcc STATIC
	${PROJECT_SOURCE_DIR}/lib/assert.c
	${PROJECT_SOURCE_DIR}/lib/bbexit.c
	${PROJECT_SOURCE_DIR}/lib/yynull.c
)
set_target_properties(liblcc PROPERTIES OUTPUT_NAME lcc)

#
# install target
#

include(GNUInstallDirs)

install(
	TARGETS
		lcc
		lcc-rcc
		lcc-cpp
		bprint
	DESTINATION
		bin
)

install(
	TARGETS
		liblcc
	DESTINATION
		lib
)

install(
	FILES
		${PROJECT_SOURCE_DIR}/doc/bprint.1
		${PROJECT_SOURCE_DIR}/doc/lcc.1
	DESTINATION
		man/man1
)

cmake_minimum_required(VERSION 3.28)
project(lcc LANGUAGES C VERSION 4.2.0)

# packages
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
# lburg
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

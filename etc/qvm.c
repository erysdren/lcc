/* quake3 bytecode target */

#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#define BINEXT ".exe"
#define COPYCMD "copy"
#define PATH_SEP '\\'
#else
#define BINEXT ""
#define COPYCMD "cp"
#define PATH_SEP '/'
#endif

#if defined(HAS_Q3ASM)
#define Q3ASMCMD "q3asm"
#elif defined(HAS_Q3ASM2)
#define Q3ASMCMD "q3asm2"
#endif

char *suffixes[] = { ".c", ".i", ".asm", ".o", ".qvm", 0 };
char inputs[256] = "";
char *cpp[] = { "lcc-cpp" BINEXT,
	"-D__STDC__=1", "-D__STRICT_ANSI__", "-D__signed__=signed", "-DQ3_VM=1",
	"$1", "$2", "$3", 0 };
char *include[] = { 0 };
char *com[] = { "lcc-rcc" BINEXT, "-target=qvm", "$1", "$2", "$3", 0 };
#ifdef Q3ASMCMD
char *ld[] = { Q3ASMCMD BINEXT, "-o", "$3", "$1", "$2", 0 };
char *as[] = { COPYCMD, "$1", "$2", "$3", 0 };
#else
char *ld[] = { 0 };
char *as[] = { 0 };
#endif

extern char *concat(char *, char *);

int option(char *arg) {
	if (strncmp(arg, "-lccdir=", 8) == 0) {
		cpp[0] = concat(&arg[8], "/lcc-cpp" BINEXT);
		include[0] = concat("-I", concat(&arg[8], "/include"));
		com[0] = concat(&arg[8], "/lcc-rcc" BINEXT);
	} else if (strncmp(arg, "-lcppdir=", 9) == 0) {
		cpp[0] = concat(&arg[9], "/lcc-cpp" BINEXT);
	} else if (strncmp(arg, "-lrccdir=", 9) == 0) {
		com[0] = concat(&arg[9], "/lcc-rcc" BINEXT);
	} else if (strcmp(arg, "-p") == 0 || strcmp(arg, "-pg") == 0) {
		fprintf( stderr, "no profiling supported, %s ignored.\n", arg);
	} else if (strcmp(arg, "-b") == 0) {
		;
	} else if (strcmp(arg, "-g") == 0) {
		fprintf( stderr, "no debugging supported, %s ignored.\n", arg);
	} else if (strncmp(arg, "-ld=", 4) == 0 || strcmp(arg, "-static") == 0) {
		ld[0] = &arg[4];
	} else if (strncmp(arg, "-as=", 4) == 0) {
		as[0] = &arg[4];
	} else {
		return 0;
	}
	return 1;
}

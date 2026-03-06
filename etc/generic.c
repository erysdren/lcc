/* bytecode target */

#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#define BINEXT ".exe"
#define PATH_SEP '\\'
#else
#define BINEXT ""
#define PATH_SEP '/'
#endif

char *suffixes[] = { ".c", ".i", ".asm", ".o", ".out", 0 };
char inputs[256] = "";
char *cpp[] = { "lcc-cpp" BINEXT,
	"-D__STDC__=1", "-D__STRICT_ANSI__", "-D__signed__=signed",
	"$1", "$2", "$3", 0 };
char *include[] = { 0 };
char *com[] = { "lcc-rcc" BINEXT, "$1", "$2", "$3", 0 };
char *ld[] = { 0 };
char *as[] = { 0 };

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
	} else if (strcmp(arg, "-b") == 0)
		;
	else if (strcmp(arg, "-g") == 0)
		fprintf( stderr, "no debugging supported, %s ignored.\n", arg);
	else if (strncmp(arg, "-ld=", 4) == 0 || strcmp(arg, "-static") == 0) {
		fprintf( stderr, "no linking supported, %s ignored.\n", arg);
	} else
		return 0;
	return 1;
}

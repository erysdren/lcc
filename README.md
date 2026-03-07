# lcc, A Retargetable Compiler for ANSI C

this is where i'm hacking on [lcc](https://github.com/drh/lcc)

added:
- CMake-based build system
- general code cleanup and fixes for C23
- made Quake 3 bytecode target (QVM) the main focus

todo:
- add C language extensions as i see fit
- reimplement test suite
- add [WebAssembly](https://webassembly.org/) target
- merge host file handling into something that can be modified at runtime

## Building

NOTE: building requires a copy of [Bison](https://www.gnu.org/software/bison/)
available to CMake

options:
- set `-DLCC_HOST_FILE=x` on the command line where `x` is one of the following options:
	- `qvm.c` - Quake 3 bytecode target (default)
	- `generic.c` - generic platform-agnostic target, makes few assumptions about host system
	- `gcc-solaris.c` - "SPARCs running Solaris 2.5.1 w/GCC tools"
	- `irix.c` - "SGI big endian MIPSes running IRIX 6.2"
	- `linux.c` - "x86s running Linux"
	- `osf.c` - "DEC ALPHAs running OSF/1 V3.2A (Rev. 17)"
	- `solaris.c` - "SPARCs running Solaris 2.5.1"
	- `win32.c` - "x86s running MS Windows NT 4.0"

```bash
# to configure
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release

# to build
cmake --build build
```

## Installation

```bash
# run this command after building
cmake --build build --target install
```

by default on a modern Linux system, files will be installed to:

```
/usr/local/bin/lcc
/usr/local/bin/lcc-rcc
/usr/local/bin/lcc-cpp
/usr/local/bin/bprint
/usr/local/lib/liblcc.a
/usr/local/man/man1/bprint.1
/usr/local/man/man1/lcc.1
```

## License

the original `lcc` has a NON-COMMERCIAL license for selling products directly
based on it. but using its output (compiled binaries, bytecode output) seems to
be free to use for whatever. but I AM NOT A LAWYER.

please read the original [CPYRIGHT](./CPYRIGHT) file for more information.

## Original README

```
This hierarchy is the distribution for lcc version 4.2.

lcc version 3.x is described in the book "A Retargetable C Compiler:
Design and Implementation" (Addison-Wesley, 1995, ISBN 0-8053-1670-1).
There are significant differences between 3.x and 4.x, most notably in
the intermediate code. For details, see
https://drh.github.io/lcc/documents/interface4.pdf.

VERSION 4.2 IS INCOMPATIBLE WITH EARLIER VERSIONS OF LCC. DO NOT
UNLOAD THIS DISTRIBUTION ON TOP OF A 3.X DISTRIBUTION.

LCC is a C89 ("ANSI C") compiler designed to be highly retargetable.

LOG describes the changes since the last release.

CPYRIGHT describes the conditions under you can use, copy, modify, and
distribute lcc or works derived from lcc.

doc/install.html is an HTML file that gives a complete description of
the distribution and installation instructions.

Chris Fraser / cwf@aya.yale.edu
David Hanson / drh@drhanson.net
```

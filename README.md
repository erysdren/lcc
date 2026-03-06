# lcc, A Retargetable Compiler for ANSI C

this is where i'm hacking on [lcc](https://github.com/drh/lcc)

added:
- CMake-based build system
- general code cleanup and fixes for C23
- make bytecode target the main focus

todo:
- language extensions as i see fit
- bring in `q3asm` assembler for linking the bytecode target to `.qvm` files

## Building

```bash
# to configure
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release

# to build
cmake --build build

# to install (optional)
cmake --build build --target install
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

# c_ti83p
A library for programming C projects for TI-83+ series calculators using SDCC.
This library is under active development and everything is  subject to change without warning.

## Compilation
The source code for c_ti83p is hosted on [Github](https://github.com/mortonsc/c_ti83p).
To compile it you need [SDCC](http://sdcc.sourceforge.net/).

### Linux/OS X
To download and compile, open a terminal window and navigate to the directory you want to download it to.
Then execute the following:

    git clone https://github.com/mortonsc/c_ti83p.git
    make

### Windows
SDCC is available on Windows, so it is possible to compile c_ti83p, but there is currently no official compile script.

## Compiling with SDCC and c_ti83-
In order for a program to use c_ti83p, it must `#include c_ti83p.h`, and be linked against `tios_crt0.rel`
and `c_ti83p.lib`. `tios_crt0.rel` *must* be listed first.
For example, if you wanted to compile a program containing one source file, `main.c`, 
and have c_ti83p in a directory called `lib`, you would use the following command:

    sdcc -mz80 --std-sdcc99 --reserve-regs-iy --max-allocs-per-node 30000 --code-loc 0x9D9B --data-loc 0 \
      --no-std-crt0 lib/tios_crt0.rel lib/c_ti83p.lib main.c
This will produce `main.ihx` as output, which can be converted to a calculator executable using tools like
[hex2bin](http://hex2bin.sourceforge.net/) and [binpac8x](http://www.ticalc.org/archives/files/fileinfo/429/42915.html).

Because the compilation command is so involved, I strongly recommend automating your compilation process.
An example of a project using c_ti83p can be found [here](https://github.com/mortonsc/TIgameoflife);
you can use its makefile as a model.

## Contents
The [crt0](tios_crt0.s) is necessary for a compiled program to run on the calculator. 
All the other functions and data included with c_ti83p are listed in the `c_ti83p.h` header. The offerings include:
* defines for non-ASCII text characters and keycodes
* functions to print text in large and small font
* access to system variables, including pointers to the graph buffer and to the large areas of free RAM
* a function to allow your program to run at 15MHz, instead of the standard 6MHz (doesn't work for TI-83+)
* [Ion Fastcopy](http://wikiti.brandonw.net/index.php?title=Z80_Routines:Graphic:Fastcopy)

## License
This library is free software, licensed under the GNU GPLv3.0.
See the [license](LICENSE.txt) for details.
All code that I wrote is copyright (C) Scott Morton 2016.
All other content is copyright (C) its original owner.
Original authors of code are named when they could be identified.

## Contact
I can be contacted through email; my address is visible on my Github profile.
This library is very much a work in progress, so feel free to send me requests for new functionality.
Bug reports should include enough information to replicate the error.

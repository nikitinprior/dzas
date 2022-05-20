# dzas
Mark Ogden has completed the work I started on decompiling ZAS.COM from Hi-Tech C compiler v3.09.
Thanks to him, the executable file for CP/M can be compiled using makefile by running the command:

make

Compiling for CP/M produces only one warning:

399: unused variable definition: nameCmp (warning)

Actually, the nameCmp() function is not used by the ZAS program.
The size of the executable program for CP/M is 4 KB larger than the original image. Most likely this is due to the use of standard (not optimized) library functions.

To get an executable file using gcc, you can enter the command:

gcc -o zasx -O2 code.c cclass.c expr.c lex.c macro.c main.c kwd.c parse.c sym.c tlab.c emulate.c

When compiling with gcc, there are no diagnostic messages.

Recreating the C code, Mark Ogden made the following remark:

"Looking at the code there appears to be a bug around ENDC / ENDM processing. I suspect very few people used the capability, although it may have been fixed in the later version of ZAS which also introduced additional features."
 
Even if this error is present in the original (and restored) program, it does not affect the operation of the ZAS program when compiling the original C program.

After completing the recreation of the source code of the ZAS macro processor from Hi-Tech C compiler v3.09, my dream of creating a compiler for the UZI-180 operating system is one step closer.

Many thanks to Mark Ogden for a job well done in restoring the ZAS program from Hi-Tech C compiler v3.09.

Andrey Nikitin

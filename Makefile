#LINKER	      =	g++
#CC	     =	g++
#LDFLAGS	     =	-L/home/9/matsumoto-y-aw/lib/lapack_etc_make_no_module -llapack -lslatec -lcerf -lrefblas /home/9/matsumoto-y-aw/lib/lapack_etc_make_no_module/rrqr.a
#INCLUDE		= -I/home/9/matsumoto-y-aw/lib/lapack_etc_make_no_module/
#COPTS	     = -cpp -O3 -fmax-errors=3 --pedantic-errors -std=c++2a
##COPTS	     = -cpp -O2 -fopenmp -fmax-errors=3 -Wall --pedantic-errors -std=c++2a
##COPTS	     = -cpp -O2 -fmax-errors=3 -Wall --pedantic-errors -std=c++20
##COPTS	     = -cpp -Og -fmax-errors=3 -g -Wall --pedantic-errors -std=c++2a
##COPTS	     = -cpp -O0 -fmax-errors=3 -Wall --pedantic-errors -std=c++2a

LINKER	     = nvc++
CC	     = nvc++
LDFLAGS	    =
INCLUDE	    = -I/home/9/matsumoto-y-aw/lib/lapack_etc_make_no_module/
COPTS	     = -stdpar
#COPTS	     = -stdpar=multicore

OBJS          = main.o\

PROGRAM	      = a.out

FRC	      = force_build

all:		$(PROGRAM)

$(PROGRAM): $(OBJS)
		$(LINKER) $(COPTS) $(OBJS) -o $(PROGRAM) $(LDFLAGS)

clean:
		rm -f $(PROGRAM) *.o

.SUFFIXES: .o .cc
.cc.o :
		$(CC) $(COPTS) $(INCLUDE) -c -o $*.o $*.cc

force_build:

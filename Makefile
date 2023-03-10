LINKER	      =	g++
CC	     =	g++
LDFLAGS	     =	-L/home/9/matsumoto-y-aw/github/lapack_etc_make -llapack -lslatec -lcerf -lrefblas /home/9/matsumoto-y-aw/github/lapack_etc_make/rrqr.a
INCLUDE		= -I/home/9/matsumoto-y-aw/github/lapack_etc_make/
#COPTS	     = -cpp -O3 -fmax-errors=3 --pedantic-errors -std=c++2a
#COPTS	     = -cpp -O2 -fopenmp -fmax-errors=3 -Wall --pedantic-errors -std=c++2a
COPTS	     = -cpp -O2 -fmax-errors=3 -Wall --pedantic-errors -std=c++2a
#COPTS	     = -cpp -Og -fmax-errors=3 -g -Wall --pedantic-errors -std=c++2a
#COPTS	     = -cpp -O0 -fmax-errors=3 -Wall --pedantic-errors -std=c++2a

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


SOURCES =  rotLibIDLWrap.c quatLibIDLWrap.c rotLibIDLLoopsDbl.c rotLibIDLLoopsFlt.c \
rotationLibCDbl.c lambertprojectionsDbl.c rotationLibCFloat.c lambertprojectionsFlt.c \
quatlib.c quatlibf.c
					 

OBJECTS= $(SOURCES:.c=.o)
EXECUTABLE = rotationLibC.dylib

#  use these options if you trust the code
CFLAGS= -O3 -c -m64
OPENMP = -fopenmp
#  use the options in the next line if you need to check code
#FLAGS= FLAGS= -c -m64
LFLAGS=  -m64 -O3 --shared 
#LFLAGS=  -m64 --shared 
#FTNCOMP = gfortran
# .GE. OS 10.8 compiler
#CCOMP=llvm-gcc 
CCOMP = gcc

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CCOMP) $(LFLAGS) $(OPENMP) $(OBJECTS) -o $@

.c.o:
	$(CCOMP) $(CFLAGS) $(OPENMP) $< -o $@
	
	
clean:
	rm -f $(OBJECTS)

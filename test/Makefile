DEBUG=1

# root directory for ecolab include files and libraries
ECOLAB_HOME=../ecolab

ifneq ($(MAKECMDGOALS),clean)
include $(ECOLAB_HOME)/include/Makefile
endif

# link statically to ecolab (needed until all bugs in EcoLab 6 ironed out)
LIBS:=$(subst -lecolab,$(ECOLAB_HOME)/lib/libecolab.a,$(LIBS)) 

VPATH= .. $(ECOLAB_HOME)/include

GTESTOBJS=main.o basicOps.o add.o

EXES=

OBJS=soup.o SIMDCPU.o

ifdef ASAN
FLAGS+=-fsanitize=address -fno-omit-frame-pointer
endif

all: unittests $(EXES)

unittests: main.o $(GTESTOBJS) $(OBJS)
	$(CPLUSPLUS) $(FLAGS)  -o $@ $^ $(LIBS) -lgtest

ifneq ($(MAKECMDGOALS),clean)
-include $(UNITTESTOBJS:.o=.d) $(GTESTOBJS:.o=.d) $(EXES:=.d) localMinsky.d
endif

BASIC_CLEAN=rm -rf *.o *~ "\#*\#" core *.d *.cd *.xcd *.gcda *.gcno

clean:
	-$(BASIC_CLEAN) unittests $(EXES)

ECOLAB_HOME=$(shell pwd)/ecolab
ifneq ($(MAKECMDGOALS),clean)
# make sure EcoLab is built first, even before starting to include Makefiles
# disable AEGIS build here, as EcoLab 6 is still a little raw
build_ecolab:=$(shell cd ecolab; if $(MAKE) $(MAKEOVERRIDES) $(CPLUSPLUSOVERRIDE) AEGIS= $(JOBS) only-libs >build.log 2>&1; then echo "ecolab built"; fi)

#$(warning $(build_ecolab))
ifneq ($(build_ecolab),ecolab built)
$(warning $(shell cat ecolab/build.log))
$(error Making ecolab failed: check ecolab/build.log)
endif
include $(ECOLAB_HOME)/include/Makefile
endif

ifdef DPCPP
# GPU may not have double precision support
FLAGS+=-DUSE_FLOAT
endif

MODELS=

all: $(MODELS:=.so)

# This rule uses a header file of object descriptors
$(MODELS:=.o): %.o: %.cc 

# how to build a model
$(MODELS:=.so): %.so: %.o ../lib/libecolab$(ECOLIBS_EXT).a
	$(LINK) $(FLAGS) -shared -Wl,-rpath $(ECOLAB_HOME)/lib $*.o $(LIBS) -o $@

#make MacOS application bundles
$(MODELS:=.app): %.app: %
	$(ECOLAB_HOME)/utils/mkmacapp $<

ifneq ($(MAKECMDGOALS),clean)
include $(MODELS:=.d)
endif

clean:
	$(BASIC_CLEAN)
	rm -f $(MODELS) *.cd
	cd ecolab; $(MAKE) clean
	cd test; $(MAKE) clean

tests: $(OBJS)
	cd test && $(MAKE)  

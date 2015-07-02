# makefile
# directories where prerequisites can be found
HOMEDIR := /home/rll81
CLUSTER := ../cluster-delegator
BOOST := /home/sharker/work
PERSISTENCE := ../perseus_4_beta

INCS := -I$(CLUSTER)/include/
INCS += -I$(BOOST)/include/
INCS += -I$(PERSISTENCE)/

#libraries
LINKFLAGS := -L$(BOOST)/lib
#LINKFLAGS += -L$(GRAPHICS)/lib

LINKLIBS := -lboost_serialization
LINKLIBS += -lX11

# Variables "make" uses for implicit rules
CC := mpicxx
CXX := mpicxx
CXXFLAGS := -O3 -std=c++11 -ggdb $(INCS) -fpermissive
LDFLAGS := $(LINKFLAGS)
LDFLAGS += -Wl,-rpath,/home/sharker/work/lib
LDLIBS := $(LINKLIBS)

# additional modules to be linked with each program
PARALLEL :=  CDataPersistence.o ParallelPersistence.o

BMPPers_directory: $(PARALLEL)
	$(CC) $(LDFLAGS) $(PARALLEL) -o $@ $(LDLIBS)

clean:
	rm *.o
	rm BMPPers_directory

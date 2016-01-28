# makefile
# directories where prerequisites can be found
HOMEDIR := /home/rll81
BOOST := /usr/local
PERSISTENCE := ../perseus_4_beta

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
LDFLAGS += -Wl,-rpath,/usr/local/lib
LDLIBS := $(LINKLIBS)

# additional modules to be linked with each program
PROCESSPERSISTENCE :=  CDataPersistence.o PersistenceHandler.o

BMPPersistence: $(PROCESSPERSISTENCE)
	$(CC) $(LDFLAGS) $(PROCESSPERSISTENCE) -o $@ $(LDLIBS)

clean:
	rm *.o
	rm BMPPersistence

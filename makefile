# makefile
# directories where prerequisites can be found
HOMEDIR := ~/
PERSISTENCE := ../perseus_4_fixed

INCS += -I$(PERSISTENCE)/

#libraries
LINKFLAGS := -L/opt/X11/lib
LINKLIBS += -lX11

# Variables "make" uses for implicit rules
CXX := g++
CXXFLAGS := -O3 -std=c++11 -ggdb $(INCS) -fpermissive
LDFLAGS := $(LINKFLAGS)
LDFLAGS += -Wl,-rpath,/usr/local/lib
LDLIBS := $(LINKLIBS)

# additional modules to be linked with each program
PROCESSPERSISTENCE :=  CDataPersistence.o PersistenceHandler.o

BMPPersistence: $(PROCESSPERSISTENCE)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(PROCESSPERSISTENCE) -o $@ $(LDLIBS)

clean:
	rm *.o
	rm BMPPersistence

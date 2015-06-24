INCDIR:=include
SRCDIR:=src
OBJDIR:=bin/obj
BINDIR:=bin

CC=g++
CFLAGS=-c --std=c++11 -I$(INCDIR)/ `pkg-config gtkmm-3.0 --cflags`

all: nepalical

## Variables and rules for CAL
SOURCES_CAL:=Ad.cpp  AdData.cpp  Bs.cpp  BsData.cpp  Date.cpp  WindowT.cpp
HEADERS_CAL:=AdData.h  Ad.h  BsData.h  Bs.h  Data.h  Date.h  ex.h  helper.h  WindowT.h  Ymd.h
OBJECTS_CAL:=$(SOURCES_CAL:.cpp=.o)
FSOURCES_CAL:=$(addprefix $(SRCDIR)/nepalical/,$(SOURCES_CAL))
FHEADERS_CAL:=$(addprefix $(INCDIR)/nepalical/,$(HEADERS_CAL))
FOBJECTS_CAL:=$(addprefix $(OBJDIR)/nepalical/,$(OBJECTS_CAL))
LDFLAGS_CAL=`pkg-config gtkmm-3.0 --libs`

MAINO_CAL:=$(OBJDIR)/nepalical.o

EXEC_CAL:=$(BINDIR)/nepalical

nepalical: $(FHEADERS_CAL) $(EXEC_CAL)
$(EXEC_CAL): $(FOBJECTS_CAL) $(MAINO_CAL)
	$(CC) $(FOBJECTS_CAL) $(MAINO_CAL) -g -o $@ $(LDFLAGS_CAL)

### Common parts to both
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) $(BINDIR)
	$(CC) -o $@ $< $(CFLAGS) -g

$(OBJDIR): | $(BINDIR)
	mkdir $(OBJDIR) $(OBJDIR)/nepalical

$(BINDIR):
	mkdir $(BINDIR)

clean:
	rm -rf bin/*

install:
	mkdir /usr/share/nepalical -p
	cp nepalical.glade /usr/share/nepalical -f
	cp bin/nepalical /usr/local/bin -f

uninstall:
	rm /usr/share/nepalical -r
	rm /usr/local/bin/nepalical

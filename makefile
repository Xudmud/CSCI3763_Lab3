ROOT=.
IDIR=$(ROOT)/inc
CC=gcc
CFLAGS=-I $(IDIR) -g

ODIR=$(ROOT)/obj
LDIR=$(ROOT)/lib
SDIR=$(ROOT)/src

LIBS=-lm

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

TARGET=$(ROOT)/wic6774mst

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(TARGET) $(ODIR)/*.o $~ core $(INCDIR)/*~

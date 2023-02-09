AR=ar
ARFLAGS=-crs
CC=gcc
CFLAGS=-g -Wall

ODIR=obj

OBJS = \
alloc_value.o \
date.o \
datetime.o \
error.o \
extract_cstr.o \
extract_int8.o \
extract_int16.o \
extract_int32.o \
extract_uint8.o \
extract_uint16.o \
extract_uint32.o \
extract_utf8_str.o \
from_buffer.o \
from_FILE.o \
init.o \
insert_cstr.o \
insert_int8.o \
insert_int16.o \
insert_int32.o \
insert_uint8.o \
insert_uint16.o \
insert_uint32.o \
insert_utf8_str.o \
is_value_no_alloc.o \
size.o \
time.o \
to_buffer.o \
to_FILE.o \
tlv.o \
uuid.o

OBJ_LIST = $(patsubst %,$(ODIR)/%,$(OBJS))

$(ODIR)/%.o: %.c
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

libeontlv.a: $(OBJ_LIST)
	$(AR) $(ARFLAGS) $@ $(OBJ_LIST) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core


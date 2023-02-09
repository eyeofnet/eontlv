CC=gcc
CFLAGS=-g -Wall -I ../ -L ../

LIBS=-l eontlv

OBJS = \
eontest.o \
test_cstr.o \
test_date.o \
test_datetime.o \
test_eontlv.o \
test_int16.o \
test_int32.o \
test_int8.o \
test_time.o \
test_uint16.o \
test_uint32.o \
test_uint8.o \
test_uuid.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)


test_eontlv: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core


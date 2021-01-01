CC=gcc 
CFLAGS=-g -lm -std=c99 -Wall -pedantic

all:     buildidx key2val val2key actors bacon1

bacon1:bacon1.c hashfn.o util.o hashfn.h util.h
	$(CC) $(CFLAGS) bacon1.c hashfn.o util.o -o bacon1

bacon1.o:bacon1.c bacon1.o hashfn.h util.h
	$(CC) $(CFLAGS) -c bacon1.c hashfn.o util.o -o bacon1.o

actors:actors.c hashfn.o util.o hashfn.h util.h
	$(CC) $(CFLAGS) actors.c hashfn.o util.o -o actors

actors.o:actors.c actors.o hashfn.h util.h
	$(CC) $(CFLAGS) -c actors.c hashfn.o util.o -o actors.o

key2val:key2val.c hashfn.o util.o hashfn.h util.h
	$(CC) $(CFLAGS) key2val.c hashfn.o util.o -o key2val

key2val.o:key2val.c key2val.o util.o hashfn.h util.h
	$(CC) $(CFLAGS) -c key2val.c hashfn.o util.o -o val2key.o
	
val2key:val2key.c hashfn.o util.o hashfn.h util.h
	$(CC) $(CFLAGS) val2key.c hashfn.o util.o -o val2key

val2key.o:val2key.c val2key.o hashfn.h util.h
	$(CC) $(CFLAGS) -c val2key.c hashfn.o util.o -o val2key.o

buildidx:buildidx.c hashfn.o util.o hashfn.h util.h
	$(CC) $(CFLAGS) buildidx.c hashfn.o util.o -o buildidx

buildidx.o:buildidx.c buildidx.o hashfn.h util.h
	$(CC) $(CFLAGS) -c buildidx.c hashfn.o util.o -o buildidx.o

hashfn.o:hashfn.c hashfn.h
	$(CC) $(CFLAGS) -c hashfn.c -o hashfn.o

util.o:util.c util.h
	$(CC) $(CFLAGS) -c util.c -o util.o
clean:
	rm -f *.o util hashfn buildidx key2val val2key actors bacon1

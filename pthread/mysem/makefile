CFLAGS+=-pthread 
LDFLAGS+=-pthread 

all:mysem

mysem: main.o mysem.o
	gcc $^ -o $@ $(CFLAGS) $(LDFLAGS) 

clean:
	rm -f *.o mysem

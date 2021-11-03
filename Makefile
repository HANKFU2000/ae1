tldmonitor: tldmonitor.o date.o tldlist.o
	clang -g -Wall -Werror -o tldmonitor tldmonitor.o date.o tldlist.o

date.o: date.h date.c
	clang -g -Wall -Werror -o date.o -c date.c

tldlist.o: tldlist.h tldlist.c
	clang -g -Wall -Werror -o tldlist.o -c tldlist.c

tldmonitor.o: tldmonitor.c date.h tldlist.h
	clang -g -Wall -Werror -o tldmonitor.o -c tldmonitor.c

clean:
	rm -f *.o tldmonitor

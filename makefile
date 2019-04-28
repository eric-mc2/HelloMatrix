# compiler flags
# -g add debug info
# -Wall enable compiler warnings
# -I. include current directory
CFLAGS=-g -Wall -I.

src = $(wildcard *.cpp)
obj = $(src:.c=.o)

test: $(obj)
	g++ -std=c++11 -o $@ $^

.PHONY: clean
clean:
	rm -f $(obj) all
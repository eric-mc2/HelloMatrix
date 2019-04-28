CXXFLAGS=-g -Wall -std=c++11

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

test: $(obj)
	g++ -o $@ $^

.PHONY: clean
clean:
	rm -f $(obj) test

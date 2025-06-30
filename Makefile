CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = mc

all: $(TARGET)

$(TARGET): main.cpp mc.tab.c lex.yy.c
	$(CXX) $(CXXFLAGS) -no-pie -o $(TARGET) main.cpp mc.tab.c lex.yy.c

mc.tab.c mc.tab.h: mc.y
	bison -d mc.y

lex.yy.c: mc.l mc.tab.h
	flex mc.l

clean:
	rm -f $(TARGET) mc.tab.c mc.tab.h lex.yy.c

.PHONY: all clean

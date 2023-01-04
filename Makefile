OS=$(shell uname)
ifeq ($(OS), Linux)
	CXXFLAGS=-lgtest -g  -lpthread
	LEAKS = valgrind --leak-check=full
else
	CXXFLAGS = -lgtest -g
	LEAKS = CK_FORK=no leaks --atExit --
endif
CXX=g++ -std=c++17 -Wall -Wextra -Werror
BD = ../build/


all: build check

build: clean mk replication
	cd $(BD); qmake CPP4_3DViewer.pro
	make -C $(BD)

replication: 
	cp -r * $(BD)
	
dist: build
	cd $(BD);cd ..; tar -cvf CPP4_3DViewer.tar build

install: build
	mkdir $(HOME)/Desktop/CPP4_3DViewer/
	cp -rf $(BD)CPP4_3DViewer.app $(HOME)/Desktop/CPP4_3DViewer/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/CPP4_3DViewer/

dvi: 
	open -a "Google Chrome" dvi.html

mk:
	mkdir ../build

test:
	@$(CXX) -O0 -C test.cpp affine.cpp ModelReader.cpp -o test $(CXXFLAGS)
	./test

check:
	@clang-format -i *.cpp *.h
	clang-format -n *.cpp *.h
	cppcheck --enable=all  --language=c++ --force --suppress=unusedFunction  *.cpp *.h


clean:
	rm -rf *.gcda *.gcno *.o *.info _tests */*.out *.dSYM test
	rm -rf $(BD)*
	rm -rf $(BD)
	rm -rf ../build-*


.PHONY: check tests clean
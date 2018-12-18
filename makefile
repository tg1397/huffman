all: hencode hdecode


hencode: hencode.o heap.o
	g++ -o hencode hencode.o heap.o
hencode.o: hencode.cc
	g++ -c hencode.cc

heap.o: heap.h heap.cc
	g++ -c heap.cc

hdecode: hdecode.o
	g++ -o hdecode hdecode.o
hdecode.o: hdecode.cc
	g++ -c hdecode.cc
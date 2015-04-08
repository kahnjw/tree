all:
	g++ -o testfile test/tree_tests.cpp && ./testfile

testit:
	g++ -o testfile test/tree_tests.cpp && \
	./testfile && \
	rm ./testfile
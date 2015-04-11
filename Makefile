node_unit_test:
	g++ -o test/bin/node_unit test/node_unit.cpp

tree_unit_test:
	g++ -o test/bin/tree_unit test/tree_unit.cpp

stress_test:
	g++ -o test/bin/stress_test test/stress_test.cpp

testall:	clean node_unit_test tree_unit_test stress_test

clean:
	rm -f test/bin/stress_test test/bin/tree_unit test/bin/node_unit

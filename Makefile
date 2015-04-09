node_unit_test:
	g++ -o node_unit test/node_unit.cpp && ./node_unit && rm ./node_unit

tree_unit_test:
	g++ -o tree_unit test/tree_unit.cpp && ./tree_unit && rm ./tree_unit

unit: node_unit_test tree_unit_test

#define CATCH_CONFIG_MAIN
#include <stdlib.h>
#include <stdio.h>
#include "lib/catch/catch.hpp"
#include "../tree.hpp"

TEST_CASE("Tree can get and set nodes", "[Tree]")
{
    Tree t = Tree();
    node *n1;
    node *n2;
    node *n3;

    t.insert("first key", 1);
    t.insert("second key", -10);
    t.insert("third key", 1000);

    n1 = t.search("first key");
    n2 = t.search("second key");
    n3 = t.search("third key");

    REQUIRE(1 == n1->value);
    REQUIRE(-10 == n2->value);
    REQUIRE(1000 == n3->value);
}

TEST_CASE("Tree can update existing nodes", "[Tree]")
{
    Tree t = Tree();
    node *n;

    t.insert("test key", 9001);
    t.insert("test key", 9002);

    n = t.search("test key");

    REQUIRE(9002 == n->value);
}

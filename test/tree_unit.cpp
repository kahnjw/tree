#define CATCH_CONFIG_MAIN
#include <stdlib.h>
#include <stdio.h>
#include "lib/catch/catch.hpp"
#include "../tree.hpp"


TEST_CASE("Tree can get and set nodes", "[Tree]")
{
    Tree t = Tree();
    Node *n1;
    Node *n2;
    Node *n3;

    t.insert("first key", 1);
    t.insert("second key", -10);
    t.insert("third key", 1000);

    n1 = t.search("first key");
    n2 = t.search("second key");
    n3 = t.search("third key");

    REQUIRE(1 == n1->get_value());
    REQUIRE(-10 == n2->get_value());
    REQUIRE(1000 == n3->get_value());
}

TEST_CASE("Tree can update existing nodes", "[Tree]")
{
    Tree t = Tree();
    Node *n;

    t.insert("test key", 9001);
    t.insert("test key", 9002);

    n = t.search("test key");

    REQUIRE(9002 == n->get_value());
}

TEST_CASE("Stress test", "[Tree]")
{
    Tree t = Tree();
    Node *n;

    int i;
    string i_str;

    for(i = 0; i < 100000; i++) {
        i_str = to_string(i);
        t.insert(i_str, i);
    }

    for(i = 0; i < 100000; i++) {
        n = t.search(to_string(i));
        REQUIRE(n != NULL);
        REQUIRE(i == n->get_value());
    }
}

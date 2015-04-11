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

TEST_CASE("Trinode restructure case 0", "[Tree]")
{
    Tree t = Tree();

    Node * grandparent = new Node();
    Node * parent = new Node();
    Node * child = new Node();
    Node * uncle = new Node();
    Node * brother = new Node();
    Node * great_grandparent = new Node();

    grandparent->set_key(0);
    parent->set_key(1);
    child->set_key(2);
    uncle->set_key(3);
    brother->set_key(4);
    great_grandparent->set_key(5);

    grandparent->set_left(parent);
    grandparent->set_right(uncle);
    grandparent->set_black();

    great_grandparent->set_left(grandparent);
    great_grandparent->set_black();

    parent->set_left(child);
    parent->set_right(brother);
    parent->set_red();

    child->set_red();

    uncle->set_black();

    t.set_root(great_grandparent);
    t.trinode_restructure(child);

    REQUIRE(child->is_red());
    REQUIRE(parent->is_black());
    REQUIRE(parent->get_left() == child);
    REQUIRE(parent->get_parent() == great_grandparent);
    REQUIRE(child->get_parent() == parent);
    REQUIRE(grandparent->get_parent() == parent);
    REQUIRE(parent->get_right() == grandparent);
    REQUIRE(grandparent->get_left() == brother);
    REQUIRE(brother->get_parent() == grandparent);
    REQUIRE(grandparent->is_red());
    REQUIRE(great_grandparent->get_left() == parent);
}

TEST_CASE("Trinode restructure case 1", "[Tree]")
{
    Tree t = Tree();

    Node * grandparent = new Node();
    Node * parent = new Node();
    Node * child = new Node();
    Node * uncle = new Node();
    Node * brother = new Node();
    Node * great_grandparent = new Node();

    grandparent->set_key(0);
    parent->set_key(1);
    child->set_key(2);
    uncle->set_key(3);
    brother->set_key(4);
    great_grandparent->set_key(5);

    grandparent->set_left(parent);
    grandparent->set_right(uncle);
    grandparent->set_black();

    great_grandparent->set_left(grandparent);
    great_grandparent->set_black();

    parent->set_right(child);
    parent->set_left(brother);
    parent->set_red();

    child->set_red();
    uncle->set_black();

    t.set_root(great_grandparent);
    t.trinode_restructure(child);


    REQUIRE(child->is_black());
    REQUIRE(parent->is_red());
    REQUIRE(parent->get_left() == brother);
    REQUIRE(child->get_parent() == great_grandparent);
    REQUIRE(grandparent->get_parent() == child);
    REQUIRE(parent->get_parent() == child);
    REQUIRE(child->get_left() == parent);
    REQUIRE(child->get_right() == grandparent);
    REQUIRE(grandparent->is_red());
    REQUIRE(great_grandparent->get_left() == child);
}

TEST_CASE("Trinode restructure case 2", "[Tree]")
{
    Tree t = Tree();

    Node * grandparent = new Node();
    Node * parent = new Node();
    Node * child = new Node();
    Node * uncle = new Node();
    Node * brother = new Node();
    Node * great_grandparent = new Node();

    grandparent->set_key(0);
    parent->set_key(1);
    child->set_key(2);
    uncle->set_key(3);
    brother->set_key(4);
    great_grandparent->set_key(5);

    grandparent->set_right(parent);
    grandparent->set_left(uncle);
    grandparent->set_black();

    great_grandparent->set_right(grandparent);
    great_grandparent->set_black();

    parent->set_right(child);
    parent->set_left(brother);
    parent->set_red();

    child->set_red();
    uncle->set_black();

    t.set_root(great_grandparent);
    t.trinode_restructure(child);

    REQUIRE(child->is_red());
    REQUIRE(parent->is_black());
    REQUIRE(parent->get_right() == child);
    REQUIRE(child->get_parent() == parent);
    REQUIRE(grandparent->get_parent() == parent);
    REQUIRE(parent->get_left() == grandparent);
    REQUIRE(grandparent->get_right() == brother);
    REQUIRE(brother->get_parent() == grandparent);
    REQUIRE(grandparent->is_red());
    REQUIRE(parent->get_parent() == great_grandparent);
    REQUIRE(great_grandparent->get_right() == parent);
}

TEST_CASE("Trinode restructure case 3", "[Tree]")
{
    Tree t = Tree();

    Node * grandparent = new Node();
    Node * parent = new Node();
    Node * child = new Node();
    Node * uncle = new Node();
    Node * brother = new Node();
    Node * great_grandparent = new Node();

    grandparent->set_key(0);
    parent->set_key(1);
    child->set_key(2);
    uncle->set_key(3);
    brother->set_key(4);
    great_grandparent->set_key(5);

    grandparent->set_right(parent);
    grandparent->set_left(uncle);
    grandparent->set_black();

    great_grandparent->set_right(grandparent);
    great_grandparent->set_black();

    parent->set_left(child);
    parent->set_right(brother);
    parent->set_red();

    child->set_red();
    uncle->set_black();

    t.set_root(great_grandparent);
    t.trinode_restructure(child);


    REQUIRE(child->is_black());
    REQUIRE(parent->is_red());
    REQUIRE(parent->get_right() == brother);
    REQUIRE(child->get_parent() == great_grandparent);
    REQUIRE(grandparent->get_parent() == child);
    REQUIRE(parent->get_parent() == child);
    REQUIRE(child->get_right() == parent);
    REQUIRE(child->get_left() == grandparent);
    REQUIRE(grandparent->is_red());
    REQUIRE(great_grandparent->get_right() == child);
}

TEST_CASE("Can insert and find elements", "[Tree]")
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

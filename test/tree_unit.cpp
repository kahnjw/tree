#define CATCH_CONFIG_MAIN
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "lib/catch/catch.hpp"
#include "../tree.hpp"


TEST_CASE("Tree can get and set nodes", "[Tree]")
{
    Tree<int> t = Tree<int>();

    t.insert("first key", 1);
    t.insert("second key", -10);
    t.insert("third key", 1000);


    REQUIRE(1 == t.get("first key"));
    REQUIRE(-10 == t.get("second key"));
    REQUIRE(1000 == t.get("third key"));
}

TEST_CASE("Tree can update existing nodes", "[Tree]")
{
    Tree<int> t = Tree<int>();

    t.insert("test key", 9001);
    t.insert("test key", 9002);

    REQUIRE(9002 == t.get("test key"));
}

TEST_CASE("Trinode restructure case 0", "[Tree]")
{
    Tree<int> t = Tree<int>();

    Node<int> * grandparent = new Node<int>();
    Node<int> * parent = new Node<int>();
    Node<int> * child = new Node<int>();
    Node<int> * uncle = new Node<int>();
    Node<int> * brother = new Node<int>();
    Node<int> * great_grandparent = new Node<int>();

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
    Tree<int> t = Tree<int>();

    Node<int> * grandparent = new Node<int>();
    Node<int> * parent = new Node<int>();
    Node<int> * child = new Node<int>();
    Node<int> * uncle = new Node<int>();
    Node<int> * brother = new Node<int>();
    Node<int> * great_grandparent = new Node<int>();

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
    Tree<int> t = Tree<int>();

    Node<int> * grandparent = new Node<int>();
    Node<int> * parent = new Node<int>();
    Node<int> * child = new Node<int>();
    Node<int> * uncle = new Node<int>();
    Node<int> * brother = new Node<int>();
    Node<int> * great_grandparent = new Node<int>();

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
    Tree<int> t = Tree<int>();

    Node<int> * grandparent = new Node<int>();
    Node<int> * parent = new Node<int>();
    Node<int> * child = new Node<int>();
    Node<int> * uncle = new Node<int>();
    Node<int> * brother = new Node<int>();
    Node<int> * great_grandparent = new Node<int>();

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
    Tree<int> t = Tree<int>();

    int i;
    int value;
    string i_str;

    for(i = 0; i < 10000; i++) {
        i_str = std::to_string(i);
        t.insert(i_str, i);
    }

    for(i = 0; i < 10000; i++) {
        value = t.get(std::to_string(i));
        REQUIRE(i == value);
    }
}

TEST_CASE("Behaves reasonably when int Nodes are not found", "[Tree]")
{
    Tree<int> int_tree = Tree<int>();
    int_tree.insert("key", 123);
    REQUIRE(int_tree.get("fake key") == 0);
}

TEST_CASE("Behaves reasonably when double Nodes are not found", "[Tree]")
{
    Tree<double> double_tree = Tree<double>();
    double_tree.insert("key", 1.1);
    REQUIRE(double_tree.get("fake key") == 0.0);
}

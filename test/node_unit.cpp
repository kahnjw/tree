#define CATCH_CONFIG_MAIN
#include <stdlib.h>
#include <stdio.h>
#include "lib/catch/catch.hpp"
#include "../node.hpp"


TEST_CASE("Node can get parent", "[Node]")
{
    Node<int> * child = new Node<int>();
    Node<int> * parent = new Node<int>();

    child->set_parent(parent);

    REQUIRE(child->get_parent() == parent);
}

TEST_CASE("Node can get left child", "[Node]")
{
    Node<int> * parent = new Node<int>();
    Node<int> * left = new Node<int>();

    parent->set_left(left);

    REQUIRE(parent->get_left() == left);
}

TEST_CASE("Node can get right child", "[Node]")
{
    Node<int> * parent = new Node<int>();
    Node<int> * right = new Node<int>();

    parent->set_right(right);

    REQUIRE(parent->get_right() == right);
}

TEST_CASE("Node can get right sibling", "[Node]")
{
    Node<int> * parent = new Node<int>();
    Node<int> * right = new Node<int>();
    Node<int> * left = new Node<int>();

    parent->set_right(right);
    parent->set_left(left);

    /* Node's must have unique keys to be
     * uniquely identifyable
     */
    right->set_key(0);
    left->set_key(1);
    parent->set_key(2);

    right->set_parent(parent);
    left->set_parent(parent);

    REQUIRE(left->get_sibling() == right);
}

TEST_CASE("Node can get left sibling", "[Node]")
{
    Node<int> * parent = new Node<int>();
    Node<int> * right = new Node<int>();
    Node<int> * left = new Node<int>();

    /* Node's must have unique keys to be
     * uniquely identifyable
     */
    parent->set_right(right);
    parent->set_left(left);
    parent->set_key(2);

    right->set_key(0);
    left->set_key(1);

    right->set_parent(parent);
    left->set_parent(parent);

    REQUIRE(right->get_sibling() == left);
}

TEST_CASE("Node can get left NULL sibling", "[Node]")
{
    Node<int> * parent = new Node<int>();
    Node<int> * right = new Node<int>();
    Node<int> * left = NULL;

    /* Node's must have unique keys to be
     * uniquely identifyable
     */
    parent->set_right(right);
    parent->set_left(left);
    parent->set_key(2);

    right->set_key(0);

    right->set_parent(parent);

    REQUIRE(right->get_sibling() == left);
}

TEST_CASE("Node can get right NULL sibling", "[Node]")
{
    Node<int> * parent = new Node<int>();
    Node<int> * left = new Node<int>();
    Node<int> * right = NULL;

    /* Node's must have unique keys to be
     * uniquely identifyable
     */
    parent->set_right(right);
    parent->set_left(left);
    parent->set_key(2);

    left->set_key(0);

    left->set_parent(parent);

    REQUIRE(left->get_sibling() == right);
}

TEST_CASE("Node can determine if it is on the right", "[Node]")
{
    Node<int> * parent = new Node<int>();
    Node<int> * right = new Node<int>();
    Node<int> * left = new Node<int>();

    /* Node's must have unique keys to be
     * uniquely identifyable
     */
    parent->set_right(right);
    parent->set_left(left);
    parent->set_key(2);

    right->set_key(0);
    left->set_key(1);

    right->set_parent(parent);
    left->set_parent(parent);

    REQUIRE(!right->is_left());
}

TEST_CASE("Node can determine if it is on the left", "[Node]")
{
    Node<int> * parent = new Node<int>();
    Node<int> * right = new Node<int>();
    Node<int> * left = new Node<int>();

    /* Node's must have unique keys to be
     * uniquely identifyable
     */
    parent->set_right(right);
    parent->set_left(left);
    parent->set_key(2);

    right->set_key(0);
    left->set_key(1);

    right->set_parent(parent);
    left->set_parent(parent);

    REQUIRE(left->is_left());
}

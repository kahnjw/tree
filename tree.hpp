#include <stdlib.h>
#include <stdio.h>
#include "node.hpp"

using namespace std;


class Tree
{
    public:
        Tree();
        ~Tree();

        void insert(string key, int value);
        Node *search(string key);
        void destroy_tree();
        void print();

    private:
        bool is_left(Node * node);
        int string_to_hash(string key);
        void destroy_tree(Node *leaf);
        void insert(int key, int value, Node *leaf);
        void print(Node *leaf);
        void doubleRed(Node * child);
        void trinode_restructure(Node * child);
        Node *search(int key, Node *leaf);

        Node *root;
};

Tree::Tree()
{
    root = NULL;
}

Tree::~Tree()
{
    destroy_tree();
}

int Tree::string_to_hash(string key)
{
    /* TODO: Use a more robust hashing algorithm */
    hash<string> str_hash;

    return str_hash(key);
}

void Tree::trinode_restructure(Node * child)
{
    Node * parent;
    Node * grandparent;
    Node * brother;
    Node * uncle;
    Node * great_grand_parent;

    parent = child->get_parent();
    uncle = parent->get_sibling();
    grandparent = parent->get_parent();
    great_grand_parent = grandparent->get_parent();

    if(child->is_left() && parent->is_left()) {

        brother = child->get_sibling();

        grandparent->set_left(brother);
        grandparent->set_right(uncle);
        grandparent->set_parent(parent);

        parent->set_right(grandparent);
        parent->set_parent(great_grand_parent);

        if(brother != NULL) {
            brother->set_parent(grandparent);
        }

    } else if(!child->is_left() && parent->is_left()) {
        // TODO
    }
}

void Tree::doubleRed(Node * child)
{
    Node * parent;
    Node * grand_parent;
    Node * uncle;

    parent = child->get_parent();

    if(parent == NULL) {
        printf("Node's parent is NULL");
        exit(1);
    }

    grand_parent = parent->get_parent();

    if(grand_parent == NULL) {
        printf("Node's grandparent is NULL");
        exit(1);
    }

    uncle = parent->get_sibling();

    if(uncle == NULL || uncle->is_black()) {
        trinode_restructure(child);
    } else {
        // recoloring();
    }
}

/* Tree insert takes a key, a value, and a Node pointer
 * Returns void.
 *
 * This function is a tail recursive depth first insert
 * algorithm. The time complexity in the worst case is
 * O(N). On average it will be O(log(N)) assuming the
 * tree is reasonably balanced.
 */
void Tree::insert(int key, int value, Node *leaf)
{
    Node * new_node;

    if(key < leaf->get_key()) {

        if(leaf->get_left() != NULL) {
            return insert(key, value, leaf->get_left());
        } else {
            new_node = new Node();
            new_node->set_key(key);
            new_node->set_value(value);
            new_node->set_red();
            new_node->set_parent(leaf);
            leaf->set_left(new_node);

            if(leaf->is_red()) {
                doubleRed(new_node);
            }
        }

    } else if(key > leaf->get_key()) {

        if(leaf->get_right() != NULL) {
            return insert(key, value, leaf->get_right());
        } else {
            new_node = new Node();
            new_node->set_key(key);
            new_node->set_value(value);
            new_node->set_red();
            new_node->set_parent(leaf);
            leaf->set_right(new_node);

            if(leaf->is_red()) {
                doubleRed(new_node);
            }
        }

    } else if(key == leaf->get_key()) {
        leaf->set_value(value);
    }
}

/* Tree search takes a key, and a Node pointer
 * Returns a Node *.
 *
 * This function is a tail recursive depth first search
 * algorithm. The time complexity in the worst case is
 * O(N). On average it will be O(log(N)) assuming the
 * tree is reasonably balanced.
 */
Node *Tree::search(int key, Node *leaf)
{
    if(leaf != NULL) {

        if(key == leaf->get_key()) {
            return leaf;
        } else if (key < leaf->get_key()) {
            return search(key, leaf->get_left());
        }

        return search(key, leaf->get_right());

    }

    return NULL;
}

void Tree::insert(string key, int value)
{
    int hash_key = string_to_hash(key);

    if(root != NULL) {
        insert(hash_key, value, root);
    } else {
        root = new Node();
        root->set_value(value);
        root->set_key(hash_key);
        root->set_black();
    }
}

Node *Tree::search(string key)
{
    int hash_key = string_to_hash(key);
    return search(hash_key, root);
}

void Tree::destroy_tree()
{
    delete root;
}

void Tree::print(Node *leaf)
{
    if(leaf->get_left() != NULL) {
        print(leaf->get_left());
    }

    if(leaf->get_right() != NULL) {
        print(leaf->get_right());
    }
}

void Tree::print()
{
    print(root);
}

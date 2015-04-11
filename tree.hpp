#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "node.hpp"

using namespace std;

template <class ObjectType>
class Tree
{
    public:
        Tree();
        ~Tree();

        void insert(string key, ObjectType value);
        Node<ObjectType> *search(string key);
        void trinode_restructure(Node<ObjectType> * child);
        void recolor(Node<ObjectType> * child);
        void set_root(Node<ObjectType> * _node);
        long sdbm(const char * str);

    private:
        bool is_root(Node<ObjectType> * node);
        void insert(long key, ObjectType value, Node<ObjectType> *leaf);
        void doubleRed(Node<ObjectType> * child);
        Node<ObjectType> * search(long key, Node<ObjectType> *leaf);

        Node<ObjectType> * root;
};

template <class ObjectType>
Tree<ObjectType>::Tree()
{
    root = NULL;
}

template <class ObjectType>
Tree<ObjectType>::~Tree()
{
    delete root;
}

template <class ObjectType>
void Tree<ObjectType>::set_root(Node<ObjectType> * _node)
{
    root = _node;
}

template <class ObjectType>
bool Tree<ObjectType>::is_root(Node<ObjectType> * node)
{
    return node == root;
}

template <class ObjectType>
long Tree<ObjectType>::sdbm (const char * str)
{
    long hash = 0;
    int c;

    /* Move through the char * bit by bit, scramble hash
     * and add it to the accumulated hash value.
     */
    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

template <class ObjectType>
void Tree<ObjectType>::trinode_restructure(Node<ObjectType> * child)
{
    bool grandparent_is_left;
    Node<ObjectType> * parent;
    Node<ObjectType> * grandparent;
    Node<ObjectType> * great_grandparent;
    Node<ObjectType> * brother;

    brother = child->get_sibling();
    parent = child->get_parent();
    grandparent = parent->get_parent();
    great_grandparent = grandparent->get_parent();
    grandparent_is_left = grandparent->is_left();

    if (child->is_left() && parent->is_left()) {

        grandparent->set_left(brother);
        parent->set_right(grandparent);

        if (grandparent_is_left && great_grandparent != NULL) {
            great_grandparent->set_left(parent);
        } else if (great_grandparent != NULL) {
            great_grandparent->set_right(parent);
        } else if (is_root(grandparent)) {
            root = parent;
            parent->set_parent(NULL);
        }

        parent->set_black();
        grandparent->set_red();

    } else if (child->is_right() && parent->is_left()) {

        parent->set_right(child->get_left());

        grandparent->set_left(child->get_right());

        child->set_left(parent);
        child->set_right(grandparent);

        if (grandparent_is_left && great_grandparent != NULL) {
            great_grandparent->set_left(child);
        } else if (great_grandparent != NULL) {
            great_grandparent->set_right(child);
        } else if (is_root(grandparent)) {
            root = child;
            child->set_parent(NULL);
        }

        child->set_black();
        grandparent->set_red();

    } else if (child->is_right() && parent->is_right()) {

        grandparent->set_right(brother);
        parent->set_left(grandparent);

        if (grandparent_is_left && great_grandparent != NULL) {
            great_grandparent->set_left(parent);
        } else if (great_grandparent != NULL) {
            great_grandparent->set_right(parent);
        } else if (is_root(grandparent)) {
            root = parent;
            parent->set_parent(NULL);
        }

        grandparent->set_red();
        parent->set_black();

    } else if (child->is_left() && parent->is_right()) {

        parent->set_left(child->get_right());

        grandparent->set_right(child->get_left());

        child->set_right(parent);
        child->set_left(grandparent);

        if (grandparent_is_left && great_grandparent != NULL) {
            great_grandparent->set_left(child);
        } else if (great_grandparent != NULL) {
            great_grandparent->set_right(child);
        } else if (is_root(grandparent)) {
            root = child;
            child->set_parent(NULL);
        }

        child->set_black();
        grandparent->set_red();

    }
}

template <class ObjectType>
void Tree<ObjectType>::doubleRed(Node<ObjectType> * child)
{
    Node<ObjectType> * parent;
    Node<ObjectType> * grandparent;
    Node<ObjectType> * great_grandparent;
    Node<ObjectType> * uncle;

    parent = child->get_parent();

    if(parent == NULL) {
        printf("Node's parent is NULL");
        exit(1);
    }

    grandparent = parent->get_parent();

    if(grandparent == NULL) {
        printf("Node's grandparent is NULL");
        exit(1);
    }

    uncle = parent->get_sibling();

    if(uncle == NULL || uncle->is_black()) {
        return trinode_restructure(child);
    } else {
        parent->set_black();
        uncle->set_black();

        if(grandparent != NULL && (!is_root(grandparent))) {
            grandparent->set_red();
            great_grandparent = grandparent->get_parent();

            if(great_grandparent != NULL && great_grandparent->is_red()) {
                return doubleRed(grandparent);
            }
        }
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
template <class ObjectType>
void Tree<ObjectType>::insert(long key, ObjectType value, Node<ObjectType> *leaf)
{
    Node<ObjectType> * new_node;

    if (key < leaf->get_key()) {

        if (leaf->get_left() != NULL) {
            return insert(key, value, leaf->get_left());
        } else {
            new_node = new Node<ObjectType>();
            new_node->set_key(key);
            new_node->set_value(value);
            leaf->set_left(new_node);

            if(leaf->is_red()) {
                return doubleRed(new_node);
            }
        }

    } else if (key > leaf->get_key()) {

        if (leaf->get_right() != NULL) {
            return insert(key, value, leaf->get_right());
        } else {
            new_node = new Node<ObjectType>();
            new_node->set_key(key);
            new_node->set_value(value);
            leaf->set_right(new_node);

            if (leaf->is_red()) {
                return doubleRed(new_node);
            }
        }

    } else if (key == leaf->get_key()) {
        return leaf->set_value(value);
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
template <class ObjectType>
Node<ObjectType> *Tree<ObjectType>::search(long key, Node<ObjectType> *leaf)
{

    if (leaf != NULL) {
        if (key == leaf->get_key()) {
            return leaf;
        } else if (key < leaf->get_key()) {
            return search(key, leaf->get_left());
        }

        return search(key, leaf->get_right());
    }

    return NULL;
}

template <class ObjectType>
void Tree<ObjectType>::insert(string key, ObjectType value)
{
    const long hash_key = sdbm(key.c_str());

    if (root != NULL) {
        insert(hash_key, value, root);
    } else {
        root = new Node<ObjectType>();
        root->set_value(value);
        root->set_key(hash_key);
        root->set_black();
    }
}

template <class ObjectType>
Node<ObjectType> *Tree<ObjectType>::search(string key)
{
    const long hash_key = sdbm(key.c_str());
    return search(hash_key, root);


}

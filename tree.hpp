#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "node.hpp"

using namespace std;


class Tree
{
    public:
        Tree();
        ~Tree();

        void insert(string key, int value);
        Node *search(string key);
        void print();
        void trinode_restructure(Node * child);
        void recolor(Node * child);
        void set_root(Node * _node);
        int string_to_hash(string key);

    private:
        bool is_root(Node * node);
        void insert(int key, int value, Node *leaf);
        void print(Node * root);
        void doubleRed(Node * child);
        Node *search(int key, Node *leaf);

        Node *root;
};

Tree::Tree()
{
    root = NULL;
}

Tree::~Tree()
{
    delete root;
}

void Tree::set_root(Node * _node)
{
    root = _node;
}

bool Tree::is_root(Node * node)
{
    return node == root;
}

int Tree::string_to_hash(string key)
{
    /* TODO: Use a more robust hashing algorithm */
    hash<string> str_hash;

    return str_hash(key);
}

void Tree::trinode_restructure(Node * child)
{
    bool grandparent_is_left;
    Node * parent;
    Node * grandparent;
    Node * great_grandparent;
    Node * brother;

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

void Tree::doubleRed(Node * child)
{
    Node * parent;
    Node * grandparent;
    Node * great_grandparent;
    Node * uncle;

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
void Tree::insert(int key, int value, Node *leaf)
{
    Node * new_node;

    if (key < leaf->get_key()) {

        if (leaf->get_left() != NULL) {
            return insert(key, value, leaf->get_left());
        } else {
            new_node = new Node();
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
            new_node = new Node();
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
Node *Tree::search(int key, Node *leaf)
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

void Tree::insert(string key, int value)
{
    int hash_key = string_to_hash(key);

    if (root != NULL) {
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

void Tree::print(Node *root)
{
    vector<Node *> level;
    vector<Node *> next_level;
    int i;

    level.push_back(root);

    while(level.size() > 0) {
        for(i = 0; i < level.size(); i++) {
            if(level[i] != NULL)
                printf("%13d %d", level[i]->get_key(), level[i]->is_red());
            else
                printf("%15s", "NULL");


            if(level[i] != NULL && level[i]->get_left() != NULL) {
                next_level.push_back(level[i]->get_left());
            } else if (level[i] != NULL) {
                next_level.push_back(NULL);
            }

            if(level[i] != NULL && level[i]->get_right() != NULL) {
                next_level.push_back(level[i]->get_right());
            } else if (level[i] != NULL) {
                next_level.push_back(NULL);
            }
        }
        printf("\n");
        level.clear();
        level.swap(next_level);
        next_level.clear();
    }
}

void Tree::print()
{
    printf("\n");
    printf("===============================================================");
    printf("===============================================================\n");
    print(root);
    printf("===============================================================");
    printf("===============================================================\n");
}

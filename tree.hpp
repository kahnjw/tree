#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct node
{
    int key;
    int value;
    node *left;
    node *right;
};

class Tree
{
    public:
        Tree();
        ~Tree();

        void insert(string key, int value);
        node *search(string key);
        void destroy_tree();
        void print();

    private:
        int string_to_hash(string key);
        void destroy_tree(node *leaf);
        void insert(int key, int value, node *leaf);
        void print(node *leaf);
        node *search(int key, node *leaf);

        node *root;
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

void Tree::destroy_tree(node *leaf)
{
    if(leaf != NULL) {
        destroy_tree(leaf->right);
        destroy_tree(leaf->left);
        delete leaf;
    }
}

void Tree::insert(int key, int value, node *leaf)
{
    if(key < leaf->key) {
        if(leaf->left != NULL) {
            insert(key, value, leaf->left);
        } else {
            leaf->left = new node;
            leaf->left->key = key;
            leaf->left->value = value;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
        }
    } else if(key > leaf->key) {
        if(leaf->right != NULL) {
            insert(key, value, leaf->right);
        } else {
            leaf->right = new node;
            leaf->right->key = key;
            leaf->right->value = value;
            leaf->right->left = NULL;
            leaf->right->right = NULL;
        }
    } else if(key == leaf->key) {
        leaf->value = value;
    }
}

node *Tree::search(int key, node *leaf)
{
    if(leaf != NULL) {
        if(key == leaf->key) {
            return leaf;
        } else if (key < leaf->key) {
            return search(key, leaf->left);
        }
        return search(key, leaf->right);
    }
    return NULL;
}

void Tree:: insert(string key, int value)
{
    int hash_key = string_to_hash(key);

    if(root != NULL) {
        insert(hash_key, value, root);
    } else {
        root = new node;
        root->value = value;
        root->key = hash_key;
        root->left = NULL;
        root->right = NULL;
    }
}

node *Tree::search(string key)
{
    int hash_key = string_to_hash(key);
    return search(hash_key, root);
}

void Tree::destroy_tree()
{
    destroy_tree(root);
}

void Tree::print(node *leaf)
{
    if(leaf->left != NULL) {
        print(leaf->left);
    }

    if(leaf->right != NULL) {
        print(leaf->right);
    }
}

void Tree::print()
{
    print(root);
}

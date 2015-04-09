#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Node
{
    public:
        Node();
        ~Node();

        int get_value();
        void set_value(int value);
        int get_key();
        void set_key(int key);
        Node * get_left();
        Node * get_right();
        Node * get_parent();
        Node * get_sibling();
        void set_left(Node * left);
        void set_right(Node * right);
        bool is_red();
        bool is_black();
        bool is_left();
        bool is_right();
        void set_red();
        void set_black();
        void set_parent(Node * parent);

    private:
        Node * left;
        Node * right;
        Node * parent;
        int key;
        int value;
        bool red;
};

Node::Node()
{
    left = NULL;
    right = NULL;
    key = 0;
    value = 0;
    red = true;
    parent = NULL;
}

Node::~Node()
{
    delete left;
    delete right;
}

int Node::get_value()
{
    return value;
}

void Node::set_value(int _value)
{
    value = _value;
}

int Node::get_key()
{
    return key;
}

void Node::set_key(int _key)
{
    key = _key;
}

Node * Node::get_left()
{
    return left;
}

Node * Node::get_right()
{
    return right;
}

Node * Node::get_parent()
{
    return parent;
}

void Node::set_left(Node * _left)
{
    left = _left;
}

void Node::set_right(Node * _right)
{
    right = _right;
}

bool Node::is_red()
{
    return red;
}

bool Node::is_black()
{
    return !red;
}

void Node::set_red()
{
    red = true;
}

void Node::set_black()
{
    red = false;
}

void Node::set_parent(Node * _parent)
{
    parent = _parent;
}

Node * Node::get_sibling()
{
    Node * parent;
    bool is_left_child;

    parent = get_parent();

    /* If node has no parent, it is the root
     * node, return NULL.
     */
    if(parent == NULL) {
        return NULL;
    }

    is_left_child = is_left();

    if(is_left_child) {
        return parent->get_right();
    }

    return parent->get_left();
}

bool Node::is_left()
{
    Node * parent;
    Node * left;

    parent = get_parent();

    /* If node has no parent, it is the root
     * node, return NULL.
     */
    if(parent == NULL) {
        return false;
    }

    left = parent->get_left();

    /* If the left child is NULL, left must be the
     * sibling of node, because we know node is
     * not NULL.
     */
    if(left == NULL) {
        return false;
    }

    /* If the key of the parent's left child
     * equals the key of the node in question
     * then the node in question is the left
     * child, and the sibling is the right
     * child.
     */
    if(left->get_key() == get_key()) {
        return true;
    }

    /* If the above condition does not hold
     * the node in question must be the right
     * node, and its sibling is the left node.
     */
    return false;
}

bool Node::is_right()
{
    return !is_left();
}

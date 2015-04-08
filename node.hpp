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
        void set_left(Node * left);
        void set_right(Node * right);

    private:
        Node * left;
        Node * right;
        int key;
        int value;
};

Node::Node()
{
    left = NULL;
    right = NULL;
    key = 0;
    value = 0;
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

void Node::set_left(Node * _left)
{
    left = _left;
}

void Node::set_right(Node * _right)
{
    right = _right;
}
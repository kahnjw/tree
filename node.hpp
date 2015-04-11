#include <stdlib.h>
#include <stdio.h>

using namespace std;

template <class ObjectType>
class Node
{
    public:
        Node();
        ~Node();

        ObjectType get_value();
        void set_value(ObjectType value);
        long get_key();
        void set_key(long key);
        Node<ObjectType> * get_left();
        Node<ObjectType> * get_right();
        Node<ObjectType> * get_parent();
        Node<ObjectType> * get_sibling();
        void set_left(Node<ObjectType> * left);
        void set_right(Node<ObjectType> * right);
        bool is_red();
        bool is_black();
        bool is_left();
        bool is_right();
        void set_red();
        void set_black();
        void set_parent(Node * parent);

    private:
        Node<ObjectType> * left;
        Node<ObjectType> * right;
        Node<ObjectType> * parent;
        long key;
        ObjectType value;
        bool red;
};

template <class ObjectType>
Node<ObjectType>::Node()
{
    left = NULL;
    right = NULL;
    key = 0;
    value = 0;
    red = true;
    parent = NULL;
}

template <class ObjectType>
Node<ObjectType>::~Node()
{
    delete left;
    delete right;
}

template <class ObjectType>
ObjectType Node<ObjectType>::get_value()
{
    return value;
}

template <class ObjectType>
void Node<ObjectType>::set_value(ObjectType _value)
{
    value = _value;
}

template <class ObjectType>
long Node<ObjectType>::get_key()
{
    return key;
}

template <class ObjectType>
void Node<ObjectType>::set_key(long _key)
{
    key = _key;
}

template <class ObjectType>
Node<ObjectType> * Node<ObjectType>::get_left()
{
    return left;
}

template <class ObjectType>
Node<ObjectType> * Node<ObjectType>::get_right()
{
    return right;
}

template <class ObjectType>
Node<ObjectType> * Node<ObjectType>::get_parent()
{
    return parent;
}

template <class ObjectType>
void Node<ObjectType>::set_left(Node * _left)
{
    left = _left;

    if(_left != NULL)
        _left->set_parent(this);
}

template <class ObjectType>
void Node<ObjectType>::set_right(Node * _right)
{
    right = _right;

    if(_right != NULL)
        _right->set_parent(this);
}

template <class ObjectType>
bool Node<ObjectType>::is_red()
{
    return red;
}

template <class ObjectType>
bool Node<ObjectType>::is_black()
{
    return !red;
}

template <class ObjectType>
void Node<ObjectType>::set_red()
{
    red = true;
}

template <class ObjectType>
void Node<ObjectType>::set_black()
{
    red = false;
}

template <class ObjectType>
void Node<ObjectType>::set_parent(Node<ObjectType> * _parent)
{
    parent = _parent;
}

template <class ObjectType>
Node<ObjectType> * Node<ObjectType>::get_sibling()
{
    Node<ObjectType> * parent;
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

template <class ObjectType>
bool Node<ObjectType>::is_left()
{
    Node<ObjectType> * parent;
    Node<ObjectType> * left;

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

    /* If the address of the parent's left child
     * equals the address of the node in question
     * then the node in question is the left
     * child, and the sibling is the right
     * child.
     */
    if(left == this) {
        return true;
    }

    /* If the above condition does not hold
     * the node in question must be the right
     * node, and its sibling is the left node.
     */
    return false;
}

template <class ObjectType>
bool Node<ObjectType>::is_right()
{
    return !is_left();
}

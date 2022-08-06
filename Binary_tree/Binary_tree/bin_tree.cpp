#include "bin_tree.h"

template<typename T>
bin_tree<T>::bin_tree()
{
    root = nullptr;
}

template<typename T>
void bin_tree<T>::delete_tree(Node<T> * node)
{
    if (node != nullptr)
    {
        Node<T> * l_branch = node->left;
        Node<T> * r_branch = node->right;
        delete node;
        delete_node(l_branch);
        delete_node(r_branch);
    }
}

template<typename T>
bin_tree<T>::~bin_tree()
{
    delete_tree(root);
}

template<typename T>
bool bin_tree<T>::is_empty() const
{
    if (root == nullptr)
        return true;
    return false;
}

template<typename T>
bool bin_tree<T>::is_elem_in_tree(T elem) const
{
    if (is_empty()) return false;
    else
    {
        Node<T>* some = root;
        do
        {
            if (elem == some->value)
                return true;
            else if (elem < some->value)
                some = some->left;
            else
                some = some->right;
        } while(some == nullptr);

        return false;
    }
}

template<typename T>
bool bin_tree<T>::insert(T elem)
{
    if (!is_elem_in_tree(elem))
    {
       Node<T> * some = root;
       while(some != nullptr)
       {
           // сравниваем
           // новое значение указателю
           if (elem < some->value)
               some = some->left;
           else
               some = some->right;
       }
       some = new Node<T>;
       some->value = elem;
       some->left = nullptr;
       some->right = nullptr;

       return true;
    }
    else return false;

}

template<typename T>
const Node<T> * bin_tree<T>::find(T elem) const
{
    Node<T> * some = root;

    while(some != nullptr)
    {
        if (some->value == elem)
            return some;
        else if (elem < some->value)
            some = some->left;
        else
            some = some->right;
    }
    return nullptr;
}

template<typename T>
void bin_tree<T>::remote(T elem)
{
    Node<T> * some = root;
    Node<T> * parent =some;

    while(some != nullptr)
    {
        if (some->value == elem)
            break;
        else if (elem < some->value)
        {
            parent = some;
            some = some->left;
        }
        else
        {
            parent = some;
            some = some->right;
        }
    }

    if (some != nullptr)
    {
        Node<T> * left_branch = some->left;
        Node<T> * right_branch = some->right;

        if (left_branch == nullptr || right_branch == nullptr)
        {
            if (parent->value < some->value)
            {
                if (left_branch == nullptr)
                    parent->right = right_branch;
                else if (right_branch == nullptr)
                    parent->right = left_branch;
            }
            else
            {
                if (left_branch == nullptr)
                    parent->left = right_branch;
                else if (right_branch == nullptr)
                    parent->left = left_branch;
            }
            delete some;
        }
        else
        {
            Node<T> * right_branch_smalest_elem = right_branch;
            Node<T> * parent_of_rbse = right_branch;

            while(right_branch_smalest_elem->left != nullptr)
            {
                parent_of_rbse = right_branch_smalest_elem;
                right_branch_smalest_elem = right_branch_smalest_elem->left;
            }
            some->value = right_branch_smalest_elem->value;
            delete right_branch_smalest_elem;
            parent_of_rbse->left = nullptr;
        }
    } //если элемента нет, нечего удалять
}

template<typename T>
const T& bin_tree<T>::find_max() const
{
    Node<T> * some = root;

    while(some->right != nullptr)
        some = some->right;

    return some->value;
}

template<typename T>
const T& bin_tree<T>::find_min() const
{
    Node<T> * some = root;

    while(some->left != nullptr)
        some = some->left;

    return some->value;
}

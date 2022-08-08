#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
//#include "bin_tree.h"

template<typename T>
struct Node
{
    T value;
    struct Node * left;
    struct Node * right;
};

template<typename T>
class bin_tree
{
private:
    struct Node<T> * root;
    bool is_elem_in_tree(T elem) const;
    bool is_empty() const;
    void delete_tree(Node<T> * node);
public:
    bin_tree();
    ~bin_tree();
    bool insert(T elem);
    void remote(T elem);
    const Node<T> * find(T elem) const;
    const T& find_max() const;
    const T& find_min() const;

};

int main()
{
    std::vector<int> vec_numbers;
    bin_tree<int> test_tree;

    std::mt19937 generator(std::time(nullptr));
    std::uniform_int_distribution<> distr(10, 99);

    std::cout << "Create vector with random elements from 1 to 100 " << std::endl;
    std::cout << "and create the bynary tree with the same elements." << std::endl;

    int number;
    for (int i = 0; i < 17; ++i)
    {
        number = distr(generator);
        vec_numbers.push_back(number);
        test_tree.insert(number);
        std::cout << number << " ";
    }
    std::cout << std::endl;

    std::cout << "find every vec element in a tree: " << std::endl;
    for(auto i : vec_numbers)
    {
        std::cout << test_tree.find(i)->value << " ";
    }
    std::cout << std::endl;

    std::random_shuffle(vec_numbers.begin(), vec_numbers.end());

    std::cout << "detele a middle of the elements in a binary tree." << std::endl;
     for (int i = 0; i < static_cast<int>(vec_numbers.size())/2; ++i)
         test_tree.remote(vec_numbers.at(i));

     std::random_shuffle(vec_numbers.begin(), vec_numbers.end());

     std::cout << "vector elements: " << std::endl;
     for (auto i : vec_numbers)
         std::cout << i << "  ";
     std::cout << std::endl;

     std::cout << "remaining tree elements: " << std::endl;

     for (auto i : vec_numbers)
     {
        auto p_int = test_tree.find(i);
        if (p_int != nullptr)
           std::cout << p_int->value << "  " ;
        else
           std::cout << "    " ;
     }
     std::cout << std::endl;

    return 0;
}
////////////////////////////////////////////////
///////////////////////////////////////////////
///
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
        delete_tree(l_branch);
        delete_tree(r_branch);
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
            else if (some->value > elem)
                some = some->left;
            else
                some = some->right;
        } while(some != nullptr);

        return false;
    }
}

template<typename T>
bool bin_tree<T>::insert(T elem)
{
    if (is_empty())
    {
        root = new Node<T>;
        root->value =elem;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    else
    {
        if (!is_elem_in_tree(elem))
        {
           Node<T> * some = root;
           Node<T> * parent = root;
           bool to_the_left;

           while(some != nullptr)
           {
               if (elem < some->value)
               {
                   parent = some;
                   some = some->left;
                   to_the_left = true;
               }
               else
               {
                   parent = some;
                   some = some->right;
                   to_the_left = false;
               }

           }
           Node<T> * new_elem = new Node<T>;
           new_elem->value = elem;
           new_elem->left = nullptr;
           new_elem->right = nullptr;
           if (to_the_left)
               parent->left = new_elem;
           else
               parent->right = new_elem;

           return true;
        }
        else return false;
    }
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
    return some;
}

template<typename T>
void bin_tree<T>::remote(T elem)
{
    Node<T> * some = root;
    Node<T> * parent = some;

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

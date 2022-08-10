#ifndef BIN_TREE_H_
#define BIN_TREE_H_

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
    bool is_empty() const;
    void delete_tree(Node<T> * node);
public:
    bin_tree();
    ~bin_tree();
    bool insert(T elem);
    void remote(T elem);
    bool is_elem_in_tree(T elem) const;
    Node<T> * find(T elem) const;
    Node<T> * find_parent(T elem) const;
    const T& find_max() const;
    const T& find_min() const;
    void clear();
};

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
Node<T> * bin_tree<T>::find(T elem) const
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
Node<T> * bin_tree<T>::find_parent(T elem) const
{
    Node<T> * some = root;
    Node<T> * parent = root;

    while(some != nullptr)
    {
        if (some->value == elem)
        {
            if (some == parent)
                return nullptr;
            return parent;
        }
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
    return nullptr;
}

template<typename T>
void bin_tree<T>::remote(T elem)
{
    if (is_elem_in_tree(elem))
    {
        Node<T> * node_for_delete = find(elem);
        Node<T> * parent_node_for_delete = find_parent(elem);
        Node<T> * left_branch = node_for_delete->left;
        Node<T> * right_branch = node_for_delete->right;

        if (left_branch != nullptr && right_branch != nullptr)
        {
            Node<T> * the_smalest_elem_in_right_branch = right_branch;
            while(the_smalest_elem_in_right_branch->left != nullptr)
                the_smalest_elem_in_right_branch = the_smalest_elem_in_right_branch->left;

            Node<T> * parent_of_the_smalest_elem_in_right_branch = find_parent(the_smalest_elem_in_right_branch->value);

            T some_value = the_smalest_elem_in_right_branch->value;
            Node<T> * right_branch_of_the_smalest = the_smalest_elem_in_right_branch->right;

            if (parent_of_the_smalest_elem_in_right_branch != node_for_delete)
                parent_of_the_smalest_elem_in_right_branch->left = right_branch_of_the_smalest;

            remote(the_smalest_elem_in_right_branch->value);

            node_for_delete->value = some_value;
        }
        else if (left_branch == nullptr)
        {
            if (parent_node_for_delete == nullptr) // root
            {
                delete node_for_delete;
                root = right_branch;
            }
            else if (parent_node_for_delete->value < node_for_delete->value)
            {
                parent_node_for_delete->right = right_branch;
                delete node_for_delete;
            }
            else
            {
                parent_node_for_delete->left = right_branch;
                delete node_for_delete;
            }
        }
        else if (right_branch == nullptr)
        {
            if (parent_node_for_delete == nullptr) // root
            {
                delete node_for_delete;
                root = left_branch;
            }
            else if (parent_node_for_delete->value < node_for_delete->value)
            {
                parent_node_for_delete->right = left_branch;
                delete node_for_delete;
            }
            else
            {
                parent_node_for_delete->left = left_branch;
                delete node_for_delete;
            }
        }
    }
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

template<typename T>
void bin_tree<T>::clear()
{
    delete_tree(root);
    root = nullptr;
}


#endif

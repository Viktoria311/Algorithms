#ifndef BIN_TREE_H
#define BIN_TREE_H

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
    //template<typename T>
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

#endif // BIN_TREE_H

#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include "bin_tree.h"


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

